/** Initialize saved badge state. */
void defaultState() {
  memset(&state, 0, sizeof(state));
  state.magic = STATE_MAGIC;
  state.version = STATE_VERSION;
  state.screen = SCREEN_HOME;
}

/** Load badge state from NVS preferences and reset incompatible versions. */
void loadState() {
  prefs.begin("pocketscout", false);
  if (prefs.getBytesLength("state") == sizeof(HackerState)) {
    prefs.getBytes("state", &state, sizeof(state));
  } else {
    defaultState();
  }
  if (state.magic != STATE_MAGIC || state.version != STATE_VERSION ||
      state.screen >= SCREEN_COUNT || state.logCount > SENSOR_LOG_SIZE ||
      state.logHead >= SENSOR_LOG_SIZE) {
    defaultState();
  }
}

/** Persist the current badge state to NVS. */
void saveState() {
  prefs.putBytes("state", &state, sizeof(state));
}

/** Store a compact sensor snapshot in the persisted ring buffer. */
void addSensorLog(const RtcDateTime &dt, const Shtc3Reading &sht, float batt) {
  uint8_t slot = state.logHead % SENSOR_LOG_SIZE;
  state.logs[slot].month = dt.month;
  state.logs[slot].day = dt.day;
  state.logs[slot].hour = dt.hour;
  state.logs[slot].minute = dt.minute;
  state.logs[slot].temp10 = sht.ok ? (int16_t)(sht.tempC * 10.0f + (sht.tempC >= 0 ? 0.5f : -0.5f)) : INT16_MIN;
  state.logs[slot].humidity10 = sht.ok ? (uint16_t)(sht.humidity * 10.0f + 0.5f) : UINT16_MAX;
  state.logs[slot].batteryMv = batt > 0 ? (uint16_t)(batt * 1000.0f + 0.5f) : 0;
  state.logs[slot].batteryPct = batteryPercent(batt);
  state.logHead = (slot + 1) % SENSOR_LOG_SIZE;
  if (state.logCount < SENSOR_LOG_SIZE) {
    state.logCount++;
  }
  saveState();
  needsRender = true;
}
