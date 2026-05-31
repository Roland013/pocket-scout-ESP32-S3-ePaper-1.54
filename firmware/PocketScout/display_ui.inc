/** Return the 5x7 bitmap glyph for one supported ASCII character. */
const uint8_t *glyphFor(char c) {
  static const uint8_t space[] = {0, 0, 0, 0, 0};
  static const uint8_t A[] = {0x7E, 0x11, 0x11, 0x11, 0x7E};
  static const uint8_t B[] = {0x7F, 0x49, 0x49, 0x49, 0x36};
  static const uint8_t C[] = {0x3E, 0x41, 0x41, 0x41, 0x22};
  static const uint8_t D[] = {0x7F, 0x41, 0x41, 0x22, 0x1C};
  static const uint8_t E[] = {0x7F, 0x49, 0x49, 0x49, 0x41};
  static const uint8_t F[] = {0x7F, 0x09, 0x09, 0x09, 0x01};
  static const uint8_t G[] = {0x3E, 0x41, 0x49, 0x49, 0x7A};
  static const uint8_t H[] = {0x7F, 0x08, 0x08, 0x08, 0x7F};
  static const uint8_t I[] = {0x00, 0x41, 0x7F, 0x41, 0x00};
  static const uint8_t J[] = {0x20, 0x40, 0x41, 0x3F, 0x01};
  static const uint8_t K[] = {0x7F, 0x08, 0x14, 0x22, 0x41};
  static const uint8_t L[] = {0x7F, 0x40, 0x40, 0x40, 0x40};
  static const uint8_t M[] = {0x7F, 0x02, 0x0C, 0x02, 0x7F};
  static const uint8_t N[] = {0x7F, 0x04, 0x08, 0x10, 0x7F};
  static const uint8_t O[] = {0x3E, 0x41, 0x41, 0x41, 0x3E};
  static const uint8_t P[] = {0x7F, 0x09, 0x09, 0x09, 0x06};
  static const uint8_t Q[] = {0x3E, 0x41, 0x51, 0x21, 0x5E};
  static const uint8_t R[] = {0x7F, 0x09, 0x19, 0x29, 0x46};
  static const uint8_t S[] = {0x46, 0x49, 0x49, 0x49, 0x31};
  static const uint8_t T[] = {0x01, 0x01, 0x7F, 0x01, 0x01};
  static const uint8_t U[] = {0x3F, 0x40, 0x40, 0x40, 0x3F};
  static const uint8_t V[] = {0x1F, 0x20, 0x40, 0x20, 0x1F};
  static const uint8_t W[] = {0x3F, 0x40, 0x38, 0x40, 0x3F};
  static const uint8_t X[] = {0x63, 0x14, 0x08, 0x14, 0x63};
  static const uint8_t Y[] = {0x07, 0x08, 0x70, 0x08, 0x07};
  static const uint8_t Z[] = {0x61, 0x51, 0x49, 0x45, 0x43};
  static const uint8_t n0[] = {0x3E, 0x51, 0x49, 0x45, 0x3E};
  static const uint8_t n1[] = {0x00, 0x42, 0x7F, 0x40, 0x00};
  static const uint8_t n2[] = {0x62, 0x51, 0x49, 0x49, 0x46};
  static const uint8_t n3[] = {0x22, 0x41, 0x49, 0x49, 0x36};
  static const uint8_t n4[] = {0x18, 0x14, 0x12, 0x7F, 0x10};
  static const uint8_t n5[] = {0x2F, 0x49, 0x49, 0x49, 0x31};
  static const uint8_t n6[] = {0x3E, 0x49, 0x49, 0x49, 0x32};
  static const uint8_t n7[] = {0x01, 0x71, 0x09, 0x05, 0x03};
  static const uint8_t n8[] = {0x36, 0x49, 0x49, 0x49, 0x36};
  static const uint8_t n9[] = {0x26, 0x49, 0x49, 0x49, 0x3E};
  static const uint8_t dot[] = {0, 0x60, 0x60, 0, 0};
  static const uint8_t colon[] = {0, 0x36, 0x36, 0, 0};
  static const uint8_t dash[] = {0x08, 0x08, 0x08, 0x08, 0x08};
  static const uint8_t slash[] = {0x20, 0x10, 0x08, 0x04, 0x02};
  static const uint8_t percent[] = {0x63, 0x13, 0x08, 0x64, 0x63};
  static const uint8_t lparen[] = {0x00, 0x1C, 0x22, 0x41, 0x00};
  static const uint8_t rparen[] = {0x00, 0x41, 0x22, 0x1C, 0x00};

  if (c >= 'a' && c <= 'z') c -= 32;
  switch (c) {
    case 'A': return A; case 'B': return B; case 'C': return C; case 'D': return D; case 'E': return E;
    case 'F': return F; case 'G': return G; case 'H': return H; case 'I': return I; case 'J': return J;
    case 'K': return K; case 'L': return L; case 'M': return M; case 'N': return N; case 'O': return O;
    case 'P': return P; case 'Q': return Q; case 'R': return R; case 'S': return S; case 'T': return T;
    case 'U': return U; case 'V': return V; case 'W': return W; case 'X': return X; case 'Y': return Y; case 'Z': return Z;
    case '0': return n0; case '1': return n1; case '2': return n2; case '3': return n3; case '4': return n4;
    case '5': return n5; case '6': return n6; case '7': return n7; case '8': return n8; case '9': return n9;
    case '.': return dot; case ':': return colon; case '-': return dash; case '/': return slash; case '%': return percent;
    case '(': return lparen; case ')': return rparen;
    default: return space;
  }
}

/** Draw one pixel if it falls inside the e-paper framebuffer bounds. */
void drawPixel(int x, int y, uint8_t color = DRIVER_COLOR_BLACK) {
  if (display && x >= 0 && x < EPD_WIDTH && y >= 0 && y < EPD_HEIGHT) {
    display->EPD_DrawColorPixel(x, y, color);
  }
}

/** Draw a 1-bit packed bitmap stored in program memory. */
void drawBitmap(int x, int y, uint8_t width, uint8_t height, const uint8_t *bitmap) {
  const uint8_t stride = (width + 7) / 8;
  for (uint8_t yy = 0; yy < height; yy++) {
    for (uint8_t xx = 0; xx < width; xx++) {
      uint8_t byte = pgm_read_byte(bitmap + yy * stride + xx / 8);
      if (byte & (0x80 >> (xx & 0x07))) {
        drawPixel(x + xx, y + yy);
      }
    }
  }
}

/** Draw a straight 1-pixel line with Bresenham-style stepping. */
void drawLine(int x0, int y0, int x1, int y1) {
  int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
  int dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
  int err = dx + dy;
  while (true) {
    drawPixel(x0, y0);
    if (x0 == x1 && y0 == y1) break;
    int e2 = 2 * err;
    if (e2 >= dy) { err += dy; x0 += sx; }
    if (e2 <= dx) { err += dx; y0 += sy; }
  }
}

/** Draw an unfilled rectangle outline. */
void drawRect(int x, int y, int w, int h) {
  drawLine(x, y, x + w - 1, y);
  drawLine(x, y + h - 1, x + w - 1, y + h - 1);
  drawLine(x, y, x, y + h - 1);
  drawLine(x + w - 1, y, x + w - 1, y + h - 1);
}

/** Fill a rectangle with black or white pixels. */
void fillRect(int x, int y, int w, int h, uint8_t color = DRIVER_COLOR_BLACK) {
  for (int yy = y; yy < y + h; yy++) {
    for (int xx = x; xx < x + w; xx++) {
      drawPixel(xx, yy, color);
    }
  }
}

/** Draw one scaled 5x7 glyph, optionally inverted for white-on-black text. */
void drawChar(int x, int y, char c, uint8_t scale = 1, bool invert = false) {
  const uint8_t *glyph = glyphFor(c);
  for (uint8_t col = 0; col < 5; col++) {
    for (uint8_t row = 0; row < 7; row++) {
      bool on = glyph[col] & (1 << row);
      uint8_t color = (on ^ invert) ? DRIVER_COLOR_BLACK : DRIVER_COLOR_WHITE;
      if (on || invert) {
        fillRect(x + col * scale, y + row * scale, scale, scale, color);
      }
    }
  }
}

/** Draw a left-aligned string with fixed-width glyph spacing. */
void drawText(int x, int y, const char *text, uint8_t scale = 1, bool invert = false) {
  int cursor = x;
  while (*text) {
    drawChar(cursor, y, *text++, scale, invert);
    cursor += 6 * scale;
  }
}

/** Return the pixel width of a string at the given glyph scale. */
int textWidth(const char *text, uint8_t scale = 1) {
  return strlen(text) * 6 * scale;
}

/** Draw a string centered horizontally at a fixed y position. */
void drawCentered(int y, const char *text, uint8_t scale = 1, bool invert = false) {
  drawText((EPD_WIDTH - textWidth(text, scale)) / 2, y, text, scale, invert);
}

/** Draw word-wrapped text and return the y position after the last line. */
int drawWrapped(int x, int y, int maxW, const char *text, uint8_t scale = 1, uint8_t maxLines = 6) {
  char line[42] = "";
  uint8_t lineLen = 0;
  uint8_t lines = 0;
  const char *p = text;
  while (*p && lines < maxLines) {
    while (*p == ' ') p++;
    char word[22] = "";
    uint8_t wl = 0;
    while (*p && *p != ' ' && wl < sizeof(word) - 1) word[wl++] = *p++;
    word[wl] = 0;
    uint8_t pendingLen = lineLen + (lineLen ? 1 : 0) + wl;
    if (pendingLen * 6 * scale > maxW && lineLen) {
      drawText(x, y + lines * 10 * scale, line, scale);
      lines++;
      line[0] = 0;
      lineLen = 0;
    }
    if (lineLen && lineLen < sizeof(line) - 1) {
      strcat(line, " ");
      lineLen++;
    }
    strncat(line, word, sizeof(line) - strlen(line) - 1);
    lineLen = strlen(line);
  }
  if (lineLen && lines < maxLines) {
    drawText(x, y + lines * 10 * scale, line, scale);
    lines++;
  }
  return y + lines * 10 * scale;
}

/** Draw a compact battery icon and percentage in the top-right corner. */
void drawBatteryStatus(float voltage) {
  uint8_t pct = batteryPercent(voltage);
  drawRect(150, 7, 18, 10);
  fillRect(168, 10, 2, 4);
  uint8_t fillW = (pct * 14) / 100;
  if (fillW > 0) {
    fillRect(152, 9, fillW, 6);
  }
  char label[6];
  snprintf(label, sizeof(label), "%u%%", pct);
  drawText(174, 8, label, 1);
}

/** Draw the common screen header with a larger compact title. */
void drawHeader(const char *title, float batt) {
  drawText(6, 5, title, 2);
  drawBatteryStatus(batt);
  drawLine(4, 27, 195, 27);
}

/** Draw active status and page number at the bottom; sleep screens intentionally omit it. */
void drawFooter(const RtcDateTime &dt, const Shtc3Reading &sht) {
  fillRect(0, 179, EPD_WIDTH, 21);
  char footer[16];
  if (sht.ok) {
    snprintf(footer, sizeof(footer), "%02u/%02u %2.0fC", dt.month, dt.day, sht.tempC);
  } else {
    snprintf(footer, sizeof(footer), "%02u/%02u --C", dt.month, dt.day);
  }
  char timeLabel[8];
  snprintf(timeLabel, sizeof(timeLabel), "%02u:%02u", dt.hour, dt.minute);
  drawText(6, 187, timeLabel, 1, true);
  drawText(72, 187, footer, 1, true);

  char pageLabel[6];
  snprintf(pageLabel, sizeof(pageLabel), "%u/%u", state.screen + 1, SCREEN_COUNT);
  drawText(EPD_WIDTH - textWidth(pageLabel, 1) - 6, 187, pageLabel, 1, true);
}

/** Draw a label/value row for dense system screens. */
void drawRow(int y, const char *label, const char *value) {
  drawText(10, y, label, 1);
  drawText(82, y, value, 1);
}

/** Draw small RSSI bars for a network row. */
void drawSignalBars(int x, int y, int32_t rssi) {
  uint8_t bars = 1;
  if (rssi > -55) bars = 4;
  else if (rssi > -65) bars = 3;
  else if (rssi > -75) bars = 2;
  for (uint8_t i = 0; i < 4; i++) {
    int h = 3 + i * 2;
    if (i < bars) fillRect(x + i * 4, y + 9 - h, 3, h);
    else drawRect(x + i * 4, y + 9 - h, 3, h);
  }
}

/** Render the home/status screen. */
void renderHome(const RtcDateTime &dt, const Shtc3Reading &sht, float batt) {
  drawHeader("HOME", batt);
  drawCentered(36, "STATUS", 2);
  drawRect(12, 62, 176, 78);
  char line[30];
  snprintf(line, sizeof(line), "%02u:%02u:%02u", dt.hour, dt.minute, dt.second);
  drawText(24, 72, line, 1);
  snprintf(line, sizeof(line), "%02u/%02u/%02u", dt.day, dt.month, dt.year % 100);
  drawText(24, 88, line, 1);
  if (sht.ok) snprintf(line, sizeof(line), "%2.0fC %2.0f%%", sht.tempC, sht.humidity);
  else snprintf(line, sizeof(line), "TEMP --");
  drawText(24, 104, line, 1);
  snprintf(line, sizeof(line), "BAT %.2FV (3.30-4.20)", batt);
  drawText(24, 120, line, 1);
  drawText(6, 154, "SHORT PRESS: NEXT", 1);
  drawText(6, 164, "LONG PRESS: ACTION", 1);
  drawFooter(dt, sht);
}

/** Render passive Wi-Fi scan results. */
void renderWifi(const RtcDateTime &dt, const Shtc3Reading &sht, float batt) {
  drawHeader("WIFI", batt);
  if (!wifiScanDone) {
    drawCentered(50, "SCAN ONLY", 2);
    drawWrapped(18, 88, 164, "HOLD BOOT TO LIST SSID RSSI CHANNEL AND SECURITY.", 1, 5);
  } else if (wifiScanResult < 0) {
    drawCentered(58, "SCAN FAILED", 2);
    drawText(22, 96, "HOLD BOOT TO RETRY", 1);
  } else if (wifiCount == 0) {
    drawCentered(58, "NO NETWORKS", 2);
    drawText(28, 96, "HOLD BOOT TO RESCAN", 1);
  } else {
    char line[42];
    uint8_t pages = (wifiCount + RADIO_RESULTS_PER_PAGE - 1) / RADIO_RESULTS_PER_PAGE;
    uint8_t start = wifiPage * RADIO_RESULTS_PER_PAGE;
    uint8_t end = min((uint8_t)(start + RADIO_RESULTS_PER_PAGE), wifiCount);
    snprintf(line, sizeof(line), "P%u/%u  %d NETS", wifiPage + 1, pages, wifiScanResult);
    drawText(10, 28, line, 1);
    for (uint8_t i = start; i < end; i++) {
      int y = 47 + (i - start) * 24;
      drawSignalBars(10, y + 2, wifiEntries[i].rssi);
      snprintf(line, sizeof(line), "%4ld C%02u %s", (long)wifiEntries[i].rssi, wifiEntries[i].channel, wifiAuthLabel(wifiEntries[i].auth));
      drawText(32, y, line, 1);
      char ssid[18];
      strncpy(ssid, wifiEntries[i].ssid, sizeof(ssid));
      ssid[sizeof(ssid) - 1] = 0;
      drawText(32, y + 10, ssid, 1);
    }
    if (pages > 1) {
      drawText(10, 169, "LONG BOOT: NEXT", 1);
    }
  }
  drawFooter(dt, sht);
}

/** Render passive BLE advertisement scan results. */
void renderBle(const RtcDateTime &dt, const Shtc3Reading &sht, float batt) {
  drawHeader("BLE", batt);
  if (!bleScanDone) {
    drawCentered(50, "BLE SCAN", 2);
    drawWrapped(18, 88, 164, "HOLD BOOT TO LIST NEARBY BLE ADS BY RSSI.", 1, 5);
  } else if (bleScanResult < 0) {
    drawCentered(58, "SCAN FAILED", 2);
    drawText(22, 96, "HOLD BOOT TO RETRY", 1);
  } else if (bleCount == 0) {
    drawCentered(58, "NO BLE ADS", 2);
    drawText(28, 96, "HOLD BOOT TO RESCAN", 1);
  } else {
    char line[32];
    uint8_t pages = bleCount;
    if (blePage >= pages) {
      blePage = 0;
    }
    const BleEntry &entry = bleEntries[blePage];
    snprintf(line, sizeof(line), "DEVICE %u/%u", blePage + 1, pages);
    drawText(10, 28, line, 1);
    drawSignalBars(10, 50, entry.rssi);
    snprintf(line, sizeof(line), "RSSI %ld", (long)entry.rssi);
    drawText(34, 49, line, 2);
    drawText(10, 72, entry.named ? "NAME" : "NO NAME", 1);
    drawWrapped(10, 86, 180, entry.name, 1, 2);
    drawText(10, 112, "SVC", 1);
    drawWrapped(34, 112, 156, entry.hasService ? entry.serviceUuid : "NONE", 1, 2);
    drawText(10, 138, "MFG", 1);
    snprintf(line, sizeof(line), "%s", entry.hasManufacturer ? entry.manufacturerId : "NONE");
    drawText(34, 138, line, 1);
    if (pages > 1) {
      drawText(10, 169, "LONG BOOT: NEXT", 1);
    }
  }
  drawFooter(dt, sht);
}

/** Render heap, uptime, and firmware status. */
void renderSystem(const RtcDateTime &dt, const Shtc3Reading &sht, float batt) {
  drawHeader("SYSTEM", batt);
  char value[24];
  uint32_t totalHeap = ESP.getHeapSize();
  uint32_t freeHeap = esp_get_free_heap_size();
  uint32_t lowHeap = esp_get_minimum_free_heap_size();
  uint8_t freePct = totalHeap ? (uint8_t)((freeHeap * 100UL) / totalHeap) : 0;
  uint8_t lowPct = totalHeap ? (uint8_t)((lowHeap * 100UL) / totalHeap) : 0;
  snprintf(value, sizeof(value), "%luK %u%%", (unsigned long)(freeHeap / 1024UL), freePct);
  drawText(10, 36, "FREE", 1);
  drawText(82, 36, value, 1);
  snprintf(value, sizeof(value), "%luK %u%%", (unsigned long)(lowHeap / 1024UL), lowPct);
  drawText(10, 56, "LOW RAM", 1);
  drawText(82, 56, value, 1);
  snprintf(value, sizeof(value), "%uS", (unsigned)(IDLE_SLEEP_MS / 1000UL));
  drawText(10, 76, "SLEEP AFTER", 1);
  drawText(82, 76, value, 1);
  snprintf(value, sizeof(value), "%.2FV (3.30-4.20)", batt);
  drawText(10, 96, "BAT", 1);
  drawText(82, 96, value, 1);
  drawText(10, 116, "TEMP HUM", 1);
  drawText(82, 116, sht.ok ? "ON" : "OFF", 1);
  drawText(10, 136, "WIFI", 1);
  drawText(82, 136, wifiScanDone ? "OFF SCAN" : "OFF", 1);
  drawText(10, 153, "BLE", 1);
  drawText(82, 153, bleScanDone ? "OFF SCAN" : "OFF", 1);
  drawFooter(dt, sht);
}

/** Render detected devices on the board I2C bus. */
void renderI2c(const RtcDateTime &dt, const Shtc3Reading &sht, float batt) {
  drawHeader("I2C", batt);
  if (!i2cScanDone) {
    drawCentered(50, "I2C BUS", 2);
    drawWrapped(22, 88, 156, "SCANNING ONBOARD I2C ADDRESSES.", 1, 5);
  } else if (i2cCount == 0) {
    drawCentered(58, "NO DEVICES", 2);
    drawText(28, 96, "HOLD BOOT TO RESCAN", 1);
  } else {
    char line[24];
    snprintf(line, sizeof(line), "%u DEVICES", i2cCount);
    drawText(10, 32, line, 2);
    for (uint8_t i = 0; i < i2cCount; i++) {
      int y = 56 + i * 18;
      snprintf(line, sizeof(line), "0X%02X  %s", i2cEntries[i].addr, i2cEntries[i].label);
      drawText(18, y, line, 2);
    }
  }
  drawFooter(dt, sht);
}

/** Render persisted sensor snapshots. */
void renderLog(const RtcDateTime &dt, const Shtc3Reading &sht, float batt) {
  drawHeader("LOG", batt);
  if (state.logCount == 0) {
    drawCentered(58, "NO LOGS", 2);
    drawWrapped(24, 96, 152, "HOLD BOOT TO STORE TEMP AND BATTERY.", 1, 4);
  } else {
    char line[40];
    for (uint8_t i = 0; i < state.logCount; i++) {
      uint8_t newest = (state.logHead + SENSOR_LOG_SIZE - 1 - i) % SENSOR_LOG_SIZE;
      const SensorLogEntry &entry = state.logs[newest];
      int y = 34 + i * 25;
      char battery[8];
      if (entry.batteryMv > 0) {
        snprintf(battery, sizeof(battery), "%u.%02uV", entry.batteryMv / 1000, (entry.batteryMv % 1000) / 10);
      } else {
        snprintf(battery, sizeof(battery), "--.--V");
      }
      if (entry.temp10 == INT16_MIN) {
        snprintf(line, sizeof(line), "%02u/%02u %02u:%02u --C --%%RH %s",
                 entry.month, entry.day, entry.hour, entry.minute, battery);
      } else {
        snprintf(line, sizeof(line), "%02u/%02u %02u:%02u %d.%uC %u%%RH %s",
                 entry.month, entry.day, entry.hour, entry.minute,
                 entry.temp10 / 10, abs(entry.temp10 % 10), entry.humidity10 / 10, battery);
      }
      drawText(10, y, line, 1);
      drawLine(10, y + 16, 190, y + 16);
    }
  }
  drawFooter(dt, sht);
}

/** Render a compact GPIO and pinout reference. */
void renderGpio(const RtcDateTime &dt, const Shtc3Reading &sht, float batt) {
  drawHeader("GPIO PINS", batt);
  char title[12];
  snprintf(title, sizeof(title), "GPIO %u/%u", gpioPage + 1, GPIO_PAGE_COUNT);
  drawText(10, 32, title, 1);
  if (gpioPage == 0) {
    drawText(10, 49, "IO0  BOOT WAKE INPUT", 1);
    drawText(10, 66, "I2C  SDA47 SCL48", 1);
    drawText(10, 83, "EPD  CS11 DC10 RST9", 1);
    drawText(10, 100, "SPI  SCK12 MOSI13", 1);
    drawText(10, 117, "EPD  BUSY8 PWR6", 1);
    drawText(10, 134, "TOUCH INT21 RST7", 1);
    drawText(10, 151, "BAT  ADC4 PWR17", 1);
    drawText(10, 168, "AUDIO PWR42 PA46", 1);
  } else {
    drawText(10, 49, "IO5  RTC INT", 1);
    drawText(10, 66, "IO13 EPD MOSI", 1);
    drawText(10, 83, "IO14 I2S MCLK", 1);
    drawText(10, 100, "IO15 I2S BCLK", 1);
    drawText(10, 117, "IO17 BAT CTRL", 1);
    drawText(10, 134, "IO18 PWR KEY", 1);
    drawText(10, 151, "IO38 I2S WS", 1);
    drawText(10, 168, "IO45 DOUT IO46 PA", 1);
  }
  drawText(10, 169, "LONG BOOT: NEXT", 1);
  drawFooter(dt, sht);
}

/** Render a no-status sleep screen before deep sleep starts. */
void renderSleepScreen() {
  drawRect(0, 0, 200, 200);
  drawBitmap((EPD_WIDTH - POCKET_SCOUT_LOGO_WIDTH) / 2, 16, POCKET_SCOUT_LOGO_WIDTH, POCKET_SCOUT_LOGO_HEIGHT, POCKET_SCOUT_LOGO);
  drawLine(30, 52, 170, 52);
  drawLine(30, 108, 170, 108);
  drawCentered(66, "POCKET SCOUT", 2);
  drawCentered(96, "PRESS PWR BUTTON", 1);
  drawText(46, 132, "RADIO OFF", 1);
}
