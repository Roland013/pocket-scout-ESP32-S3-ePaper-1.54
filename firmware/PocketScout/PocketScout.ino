/**
 * Pocket Scout firmware for the Waveshare ESP32-S3-ePaper-1.54.
 *
 * A BOOT-button controlled cyberpunk utility badge for safe, passive learning:
 * home status, passive Wi-Fi scan, system stats, and sensor logging.
 *
 * Controls:
 * - short BOOT press: next screen
 * - long BOOT press: action for the current screen
 *
 * Hardware used:
 * - 200x200 e-paper panel
 * - PCF85063 RTC over I2C
 * - SHTC3 temperature/humidity sensor over I2C
 * - battery voltage ADC through the board's switched divider
 * - ESP32-S3 Wi-Fi in scan-only mode, powered off after each scan
 */
#include <Arduino.h>
#include <BLEAdvertisedDevice.h>
#include <BLEDevice.h>
#include <BLEScan.h>
#include <Preferences.h>
#include <WiFi.h>
#include <Wire.h>
#include <math.h>
#include <string.h>
#include "driver/gpio.h"
#include "esp_bt.h"
#include "esp_sleep.h"
#include "esp_system.h"
#include "esp_wifi.h"

#include "../../third_party/waveshare_epaper_display/epaper_driver_bsp.h"
#include "pocket_scout_logo.h"

#define EPD_SPI_NUM SPI2_HOST
#define EPD_WIDTH 200
#define EPD_HEIGHT 200

#define EPD_DC_PIN GPIO_NUM_10
#define EPD_CS_PIN GPIO_NUM_11
#define EPD_SCK_PIN GPIO_NUM_12
#define EPD_MOSI_PIN GPIO_NUM_13
#define EPD_RST_PIN GPIO_NUM_9
#define EPD_BUSY_PIN GPIO_NUM_8
#define EPD_TP_INT_PIN GPIO_NUM_21
#define EPD_TP_RST_PIN GPIO_NUM_7

#define EPD_PWR_PIN GPIO_NUM_6
#define AUDIO_PWR_PIN GPIO_NUM_42
#define VBAT_PWR_PIN GPIO_NUM_17
#define BOOT_BUTTON_PIN GPIO_NUM_0
#define PWR_BUTTON_PIN GPIO_NUM_18
#define STATUS_LED_PIN GPIO_NUM_3
#define BAT_ADC_PIN 4
#define AUDIO_PA_PIN GPIO_NUM_46

#define I2C_SDA_PIN GPIO_NUM_47
#define I2C_SCL_PIN GPIO_NUM_48
#define I2C_RTC_ADDR 0x51
#define I2C_SHTC3_ADDR 0x70
#define I2C_FT6336_ADDR 0x38
#define I2C_ES8311_ADDR 0x18

static const bool ENABLE_IDLE_SLEEP = true;
static const bool STATUS_LED_ACTIVE_LOW = true;
static const uint32_t IDLE_SLEEP_MS = 120000;
static const uint8_t RADIO_RESULTS_PER_PAGE = 5;
static const uint8_t WIFI_MAX_RESULTS = 20;
static const uint8_t BLE_MAX_RESULTS = 20;
static const uint8_t I2C_MAX_RESULTS = 8;
static const uint8_t SENSOR_LOG_SIZE = 5;
static const uint8_t GPIO_PAGE_COUNT = 2;

enum ScreenMode : uint8_t {
  SCREEN_HOME = 0,
  SCREEN_SYSTEM = 1,
  SCREEN_WIFI = 2,
  SCREEN_BLE = 3,
  SCREEN_I2C = 4,
  SCREEN_LOG = 5,
  SCREEN_GPIO = 6,
  SCREEN_COUNT = 7
};

enum ButtonEvent : uint8_t {
  BTN_NONE = 0,
  BTN_SHORT = 1,
  BTN_LONG = 2
};

struct RtcDateTime {
  uint16_t year;
  uint8_t month;
  uint8_t day;
  uint8_t hour;
  uint8_t minute;
  uint8_t second;
};

struct Shtc3Reading {
  bool ok;
  float tempC;
  float humidity;
};

struct TouchPoint {
  bool ok;
  uint16_t x;
  uint16_t y;
};

struct SensorLogEntry {
  uint8_t month;
  uint8_t day;
  uint8_t hour;
  uint8_t minute;
  int16_t temp10;
  uint16_t humidity10;
  uint16_t batteryMv;
  uint8_t batteryPct;
};

struct HackerState {
  uint32_t magic;
  uint8_t version;
  uint8_t screen;
  uint8_t logCount;
  uint8_t logHead;
  SensorLogEntry logs[SENSOR_LOG_SIZE];
  uint32_t rtcBuildStamp;
};

struct WifiEntry {
  char ssid[18];
  int32_t rssi;
  uint8_t channel;
  uint8_t auth;
};

struct BleEntry {
  char name[18];
  char serviceUuid[38];
  char manufacturerId[5];
  uint8_t manufacturerLen;
  int32_t rssi;
  bool named;
  bool hasService;
  bool hasManufacturer;
};

struct I2cEntry {
  uint8_t addr;
  const char *label;
};

static const uint32_t STATE_MAGIC = 0x4841434B;
static const uint8_t STATE_VERSION = 6;

Preferences prefs;
epaper_driver_display *display = nullptr;
HackerState state;
WifiEntry wifiEntries[WIFI_MAX_RESULTS];
BleEntry bleEntries[BLE_MAX_RESULTS];
I2cEntry i2cEntries[I2C_MAX_RESULTS];
uint8_t wifiCount = 0;
uint8_t bleCount = 0;
uint8_t i2cCount = 0;
uint8_t wifiPage = 0;
uint8_t blePage = 0;
uint8_t gpioPage = 0;
int16_t wifiScanResult = 0;
int16_t bleScanResult = 0;
bool wifiScanDone = false;
bool bleScanDone = false;
bool i2cScanDone = false;
bool rtcAvailable = false;
bool touchAvailable = false;
bool needsRender = true;
uint32_t lastInputMs = 0;
uint32_t lastRenderMs = 0;
uint32_t lastWifiScanMs = 0;
uint32_t lastBleScanMs = 0;
uint32_t lastI2cScanMs = 0;
uint32_t bootMs = 0;
bool lastButtonLevel = true;
bool buttonDown = false;
bool longSent = false;
uint32_t lastButtonChangeMs = 0;
bool lastPwrButtonLevel = true;
bool pwrButtonDown = false;
bool pwrLongSent = false;
uint32_t lastPwrButtonChangeMs = 0;

#include "hardware_base.inc"
#include "sensors.inc"
#include "state_store.inc"
#include "wifi_scan.inc"
#include "ble_scan.inc"
#include "i2c_scan.inc"
#include "display_ui.inc"
#include "app_flow.inc"

#include "../../third_party/waveshare_epaper_display/epaper_driver_bsp.cpp"
