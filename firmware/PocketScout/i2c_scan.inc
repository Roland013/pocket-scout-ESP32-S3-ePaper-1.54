/** Return a friendly label for known onboard I2C devices. */
const char *i2cKnownLabel(uint8_t addr) {
  switch (addr) {
    case I2C_RTC_ADDR: return "RTC";
    case I2C_SHTC3_ADDR: return "TEMP";
    case I2C_FT6336_ADDR: return "TOUCH";
    case I2C_ES8311_ADDR: return "AUDIO";
    default: return "DEVICE";
  }
}

/** Run a standard I2C address scan on the board bus. */
void performI2cScan() {
  i2cCount = 0;
  i2cScanDone = false;
  for (uint8_t addr = 0x08; addr <= 0x77; addr++) {
    Wire.beginTransmission(addr);
    if (Wire.endTransmission() == 0 && i2cCount < I2C_MAX_RESULTS) {
      i2cEntries[i2cCount].addr = addr;
      i2cEntries[i2cCount].label = i2cKnownLabel(addr);
      i2cCount++;
    }
  }
  i2cScanDone = true;
  lastI2cScanMs = millis();
  needsRender = true;
}
