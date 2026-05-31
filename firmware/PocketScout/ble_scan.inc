/** Keep the strongest BLE advertisements sorted by RSSI. */
void insertBleEntry(const BleEntry &candidate) {
  uint8_t pos = bleCount;
  if (bleCount < BLE_MAX_RESULTS) {
    bleCount++;
  } else if (candidate.rssi <= bleEntries[BLE_MAX_RESULTS - 1].rssi) {
    return;
  } else {
    pos = BLE_MAX_RESULTS - 1;
  }

  while (pos > 0 && candidate.rssi > bleEntries[pos - 1].rssi) {
    bleEntries[pos] = bleEntries[pos - 1];
    pos--;
  }
  bleEntries[pos] = candidate;
}

/** Run a passive BLE advertisement scan, store only short names/RSSI, then power BLE down. */
void performBleScan() {
  bleCount = 0;
  blePage = 0;
  bleScanDone = false;
  bleScanResult = 0;

  BLEDevice::init("");
  BLEScan *scan = BLEDevice::getScan();
  scan->setActiveScan(false);
  scan->setInterval(160);
  scan->setWindow(80);

  BLEScanResults *results = scan->start(5, false);
  if (results) {
    bleScanResult = results->getCount();
    for (int i = 0; i < results->getCount(); i++) {
      BLEAdvertisedDevice device = results->getDevice(i);
      BleEntry entry = {};
      entry.rssi = device.getRSSI();
      entry.named = device.haveName();
      String name = entry.named ? device.getName() : "BLE DEVICE";
      name.toCharArray(entry.name, sizeof(entry.name));
      entry.hasService = device.haveServiceUUID();
      String serviceUuid = entry.hasService ? device.getServiceUUID().toString() : "NONE";
      serviceUuid.toCharArray(entry.serviceUuid, sizeof(entry.serviceUuid));
      entry.hasManufacturer = device.haveManufacturerData();
      String manufacturerData = entry.hasManufacturer ? device.getManufacturerData() : "";
      entry.manufacturerLen = manufacturerData.length();
      if (entry.manufacturerLen >= 2) {
        snprintf(entry.manufacturerId, sizeof(entry.manufacturerId), "%02X%02X",
                 (uint8_t)manufacturerData[1], (uint8_t)manufacturerData[0]);
      } else {
        strncpy(entry.manufacturerId, "NONE", sizeof(entry.manufacturerId));
        entry.manufacturerId[sizeof(entry.manufacturerId) - 1] = 0;
      }
      insertBleEntry(entry);
    }
    scan->clearResults();
  } else {
    bleScanResult = -1;
  }

  BLEDevice::deinit(true);
  if (esp_bt_controller_get_status() == ESP_BT_CONTROLLER_STATUS_ENABLED) {
    esp_bt_controller_disable();
  }
  bleScanDone = true;
  lastBleScanMs = millis();
  needsRender = true;
}

/** Advance through stored BLE result pages; scan first when no results exist. */
void nextBlePage() {
  if (!bleScanDone || bleScanResult < 0 || bleCount == 0) {
    performBleScan();
    return;
  }
  uint8_t pages = (bleCount + RADIO_RESULTS_PER_PAGE - 1) / RADIO_RESULTS_PER_PAGE;
  blePage = (blePage + 1) % pages;
  needsRender = true;
}
