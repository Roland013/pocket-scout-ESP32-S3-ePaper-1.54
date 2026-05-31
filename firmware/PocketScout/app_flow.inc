/** Clear and redraw the current app screen, then refresh the e-paper panel. */
void render() {
  if (!display) {
    return;
  }
  if (state.screen == SCREEN_I2C && !i2cScanDone) {
    performI2cScan();
  }
  RtcDateTime dt = nowDateTime();
  Shtc3Reading sht = readShtc3();
  float batt = readBatteryVoltage();
  display->EPD_Clear();
  drawRect(0, 0, 200, 200);
  switch (state.screen) {
    case SCREEN_WIFI: renderWifi(dt, sht, batt); break;
    case SCREEN_BLE: renderBle(dt, sht, batt); break;
    case SCREEN_SYSTEM: renderSystem(dt, sht, batt); break;
    case SCREEN_I2C: renderI2c(dt, sht, batt); break;
    case SCREEN_LOG: renderLog(dt, sht, batt); break;
    case SCREEN_GPIO: renderGpio(dt, sht, batt); break;
    case SCREEN_HOME:
    default: renderHome(dt, sht, batt); break;
  }
  display->EPD_Display();
  lastRenderMs = millis();
  needsRender = false;
}

/** Drive the GP3 green status LED. */
void setStatusLed(bool on) {
  bool level = STATUS_LED_ACTIVE_LOW ? !on : on;
  digitalWrite(STATUS_LED_PIN, level ? HIGH : LOW);
}

/** Blink the GP3 green status LED without leaving it on afterwards. */
void blinkStatusLed(uint8_t count, uint16_t onMs, uint16_t offMs) {
  for (uint8_t i = 0; i < count; i++) {
    setStatusLed(true);
    delay(onMs);
    setStatusLed(false);
    if (i + 1 < count) {
      delay(offMs);
    }
  }
}

/** Debounce BOOT and classify it as a short or long press. */
ButtonEvent readButtonEvent() {
  bool level = digitalRead(BOOT_BUTTON_PIN);
  uint32_t now = millis();
  if (level != lastButtonLevel && now - lastButtonChangeMs > 35) {
    lastButtonChangeMs = now;
    lastButtonLevel = level;
    if (!level) {
      buttonDown = true;
      longSent = false;
    } else if (buttonDown) {
      buttonDown = false;
      if (!longSent) {
        return BTN_SHORT;
      }
    }
  }
  if (buttonDown && !longSent && now - lastButtonChangeMs > 850) {
    longSent = true;
    return BTN_LONG;
  }
  return BTN_NONE;
}

/** Debounce PWR and use a long hold as an immediate sleep command while awake. */
ButtonEvent readPwrButtonEvent() {
  bool level = digitalRead(PWR_BUTTON_PIN);
  uint32_t now = millis();
  if (level != lastPwrButtonLevel && now - lastPwrButtonChangeMs > 35) {
    lastPwrButtonChangeMs = now;
    lastPwrButtonLevel = level;
    if (!level) {
      pwrButtonDown = true;
      pwrLongSent = false;
    } else if (pwrButtonDown) {
      pwrButtonDown = false;
    }
  }
  if (pwrButtonDown && !pwrLongSent && now - lastPwrButtonChangeMs > 1600) {
    pwrLongSent = true;
    return BTN_LONG;
  }
  return BTN_NONE;
}

/** Classify display touch as a short or long press while the device is awake. */
ButtonEvent readTouchEvent() {
  TouchPoint point = readTouch();
  uint32_t now = millis();
  if (point.ok) {
    if (!touchDown) {
      touchDown = true;
      touchLongSent = false;
      touchDownMs = now;
    } else if (!touchLongSent && now - touchDownMs > 850) {
      touchLongSent = true;
      lastTouchEventMs = now;
      return BTN_LONG;
    }
  } else if (touchDown) {
    touchDown = false;
    if (!touchLongSent && now - touchDownMs > 35 && now - lastTouchEventMs > 250) {
      lastTouchEventMs = now;
      return BTN_SHORT;
    }
  }
  return BTN_NONE;
}

/** Handle a short BOOT press by moving to the next badge screen. */
void cycleScreen() {
  blinkStatusLed(1, 40, 0);
  state.screen = (state.screen + 1) % SCREEN_COUNT;
  saveState();
  lastInputMs = millis();
  needsRender = true;
}

/** Run the current screen's long-press action. */
void handleAction() {
  blinkStatusLed(2, 120, 90);
  lastInputMs = millis();
  if (state.screen == SCREEN_WIFI) {
    nextWifiPage();
  } else if (state.screen == SCREEN_BLE) {
    nextBlePage();
  } else if (state.screen == SCREEN_I2C) {
    performI2cScan();
  } else if (state.screen == SCREEN_LOG) {
    RtcDateTime dt = nowDateTime();
    Shtc3Reading sht = readShtc3();
    float batt = readBatteryVoltage();
    addSensorLog(dt, sht, batt);
  } else if (state.screen == SCREEN_GPIO) {
    gpioPage = (gpioPage + 1) % GPIO_PAGE_COUNT;
    needsRender = true;
  } else {
    needsRender = true;
  }
}

/** Draw the sleep screen, power down peripherals, and enter BOOT-wake deep sleep. */
void enterDeepSleep() {
  saveState();
  blinkStatusLed(3, 260, 180);
  display->EPD_Clear();
  renderSleepScreen();
  display->EPD_Display();
  delay(500);

  WiFi.disconnect(true, true);
  WiFi.mode(WIFI_OFF);
  esp_wifi_stop();
  digitalWrite(AUDIO_PWR_PIN, HIGH);
  digitalWrite(AUDIO_PA_PIN, LOW);
  digitalWrite(VBAT_PWR_PIN, LOW);
  pinMode(EPD_TP_RST_PIN, OUTPUT);
  digitalWrite(EPD_TP_RST_PIN, LOW);
  digitalWrite(EPD_PWR_PIN, HIGH);
  if (esp_bt_controller_get_status() == ESP_BT_CONTROLLER_STATUS_ENABLED) {
    esp_bt_controller_disable();
  }

  gpio_hold_en(EPD_PWR_PIN);
  gpio_hold_en(AUDIO_PWR_PIN);
  gpio_hold_en(AUDIO_PA_PIN);
  gpio_hold_en(VBAT_PWR_PIN);
  gpio_hold_en(EPD_TP_RST_PIN);
  setStatusLed(false);
  gpio_hold_en(STATUS_LED_PIN);
  gpio_deep_sleep_hold_en();

  pinMode(BOOT_BUTTON_PIN, INPUT_PULLUP);
  esp_sleep_disable_wakeup_source(ESP_SLEEP_WAKEUP_ALL);
  uint64_t wakeMask = 1ULL << (uint8_t)BOOT_BUTTON_PIN;
  esp_sleep_enable_ext1_wakeup(wakeMask, ESP_EXT1_WAKEUP_ANY_LOW);
  esp_deep_sleep_start();
}

/** Enter deep sleep automatically after the configured idle period. */
void maybeSleep() {
  if (!ENABLE_IDLE_SLEEP || millis() - lastInputMs < IDLE_SLEEP_MS || millis() - lastRenderMs < 15000) {
    return;
  }
  enterDeepSleep();
}

/** Release GPIO deep-sleep holds so active-mode setup can drive pins again. */
void releaseSleepPowerHolds() {
  gpio_deep_sleep_hold_dis();
  gpio_hold_dis(EPD_PWR_PIN);
  gpio_hold_dis(AUDIO_PWR_PIN);
  gpio_hold_dis(AUDIO_PA_PIN);
  gpio_hold_dis(VBAT_PWR_PIN);
  gpio_hold_dis(EPD_TP_RST_PIN);
  gpio_hold_dis(STATUS_LED_PIN);
}

/** Restore active-mode board power rails after boot or wake. */
void setupPower() {
  pinMode(EPD_PWR_PIN, OUTPUT);
  pinMode(AUDIO_PWR_PIN, OUTPUT);
  pinMode(AUDIO_PA_PIN, OUTPUT);
  pinMode(VBAT_PWR_PIN, OUTPUT);
  digitalWrite(EPD_PWR_PIN, LOW);
  digitalWrite(AUDIO_PWR_PIN, HIGH);
  digitalWrite(AUDIO_PA_PIN, LOW);
  digitalWrite(VBAT_PWR_PIN, HIGH);
}

/** Keep radios off unless the user explicitly starts a passive Wi-Fi scan. */
void setupRadioPowerSaving() {
  WiFi.mode(WIFI_OFF);
  esp_wifi_stop();
  if (esp_bt_controller_get_status() == ESP_BT_CONTROLLER_STATUS_ENABLED) {
    esp_bt_controller_disable();
  }
}

/** Create and initialize the e-paper display driver. */
void setupDisplay() {
  custom_lcd_spi_t cfg = {};
  cfg.cs = EPD_CS_PIN;
  cfg.dc = EPD_DC_PIN;
  cfg.rst = EPD_RST_PIN;
  cfg.busy = EPD_BUSY_PIN;
  cfg.mosi = EPD_MOSI_PIN;
  cfg.scl = EPD_SCK_PIN;
  cfg.spi_host = EPD_SPI_NUM;
  cfg.buffer_len = 5000;
  display = new epaper_driver_display(EPD_WIDTH, EPD_HEIGHT, cfg);
  display->EPD_Init();
  display->EPD_Clear();
}

/** Seed the RTC from compile time once per uploaded firmware build. */
void setupRtcSeed() {
  RtcDateTime dt;
  uint32_t stamp = buildStamp();
  bool rtcOk = readRtc(dt);
  if (!rtcOk || state.rtcBuildStamp != stamp) {
    if (setRtc(buildDateTime())) {
      state.rtcBuildStamp = stamp;
      saveState();
    }
  }
}

/** Arduino entry point: initialize board state and render the current badge screen. */
void setup() {
  Serial.begin(115200);
  delay(300);
  bootMs = millis();
  releaseSleepPowerHolds();
  setupPower();
  setupRadioPowerSaving();
  pinMode(STATUS_LED_PIN, OUTPUT);
  setStatusLed(false);
  pinMode(BOOT_BUTTON_PIN, INPUT_PULLUP);
  pinMode(PWR_BUTTON_PIN, INPUT_PULLUP);
  analogReadResolution(12);
  Wire.begin(I2C_SDA_PIN, I2C_SCL_PIN);
  Wire.setClock(300000);
  detectTouch();
  loadState();
  setupRtcSeed();
  setupDisplay();
  blinkStatusLed(1, 120, 0);
  lastInputMs = millis();
  render();
}

/** Arduino main loop: handle BOOT navigation/action, render, then sleep if idle. */
void loop() {
  ButtonEvent event = readButtonEvent();
  if (event == BTN_SHORT) {
    cycleScreen();
  } else if (event == BTN_LONG) {
    handleAction();
  }
  ButtonEvent touchEvent = readTouchEvent();
  if (touchEvent == BTN_SHORT) {
    cycleScreen();
  } else if (touchEvent == BTN_LONG) {
    handleAction();
  }
  if (readPwrButtonEvent() == BTN_LONG) {
    enterDeepSleep();
  }
  if (needsRender) {
    render();
  }
  maybeSleep();
  delay(20);
}
