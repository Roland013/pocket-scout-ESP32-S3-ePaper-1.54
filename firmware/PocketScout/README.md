# Pocket Scout Firmware

Arduino sketch for Pocket Scout on the Waveshare ESP32-S3-ePaper-1.54.

For full public build and upload instructions, see the repository root
`README.md`.

## Controls

- Short BOOT press: next screen.
- Long BOOT press: action for the current screen.
- After idle timeout, the badge draws a sleep screen and enters deep sleep.
- BOOT wakes from deep sleep.

## Screens

- Home: time, date, temperature, humidity, battery voltage, battery percentage.
- System: uptime, RAM, sleep timeout, battery, Wi-Fi state, BLE state.
- Passive Wi-Fi: scan-only SSID/RSSI/channel/security list. The radio is powered off after scanning. Long BOOT scans first, then pages through stored results.
- Passive BLE: scan-only BLE advertisement details. BLE is powered off after scanning. Long BOOT scans first, then pages one device at a time.
- I2C Scanner: detected bus addresses with labels for known onboard devices.
- Sensor Log: persisted temperature and battery snapshots.
- GPIO Reference: one main page with BOOT-long subpages for display, I2C, touch, battery, RTC, and audio pins.

## Safety

The Wi-Fi screen only performs normal scan-only discovery. It does not connect,
capture traffic, collect credentials, deauthenticate clients, or attempt attacks.
The BLE screen only scans advertisements and does not connect to devices.

## Build

This firmware is Arduino-based. It compiles with Arduino CLI or Arduino IDE using
the ESP32 Arduino board package. It is not currently a native ESP-IDF project.
