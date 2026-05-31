/** Return a short label for ESP32 Wi-Fi auth mode values. */
const char *wifiAuthLabel(uint8_t auth) {
  switch ((wifi_auth_mode_t)auth) {
    case WIFI_AUTH_OPEN: return "OPEN";
    case WIFI_AUTH_WEP: return "WEP";
    case WIFI_AUTH_WPA_PSK: return "WPA";
    case WIFI_AUTH_WPA2_PSK: return "WPA2";
    case WIFI_AUTH_WPA_WPA2_PSK: return "WPA";
    case WIFI_AUTH_WPA2_ENTERPRISE: return "ENT";
    case WIFI_AUTH_WPA3_PSK: return "WPA3";
    case WIFI_AUTH_WPA2_WPA3_PSK: return "WPA3";
    default: return "SEC";
  }
}

/** Keep the strongest scan results sorted by RSSI. */
void insertWifiEntry(const WifiEntry &candidate) {
  uint8_t pos = wifiCount;
  if (wifiCount < WIFI_MAX_RESULTS) {
    wifiCount++;
  } else if (candidate.rssi <= wifiEntries[WIFI_MAX_RESULTS - 1].rssi) {
    return;
  } else {
    pos = WIFI_MAX_RESULTS - 1;
  }

  while (pos > 0 && candidate.rssi > wifiEntries[pos - 1].rssi) {
    wifiEntries[pos] = wifiEntries[pos - 1];
    pos--;
  }
  wifiEntries[pos] = candidate;
}

/** Run a safe passive Wi-Fi scan, store only SSID/RSSI/channel/security, then power Wi-Fi down. */
void performWifiScan() {
  wifiCount = 0;
  wifiPage = 0;
  wifiScanDone = false;
  wifiScanResult = 0;

  WiFi.mode(WIFI_STA);
  WiFi.disconnect(true, true);
  delay(100);

  int16_t found = WiFi.scanNetworks(false, true);
  wifiScanResult = found;
  if (found > 0) {
    for (int16_t i = 0; i < found; i++) {
      WifiEntry entry = {};
      String ssid = WiFi.SSID(i);
      if (ssid.length() == 0) {
        ssid = "HIDDEN";
      }
      ssid.toCharArray(entry.ssid, sizeof(entry.ssid));
      entry.rssi = WiFi.RSSI(i);
      entry.channel = WiFi.channel(i);
      entry.auth = (uint8_t)WiFi.encryptionType(i);
      insertWifiEntry(entry);
    }
  }

  WiFi.scanDelete();
  WiFi.disconnect(true, true);
  WiFi.mode(WIFI_OFF);
  esp_wifi_stop();
  wifiScanDone = true;
  lastWifiScanMs = millis();
  needsRender = true;
}

/** Advance through stored Wi-Fi result pages; scan first when no results exist. */
void nextWifiPage() {
  if (!wifiScanDone || wifiScanResult < 0 || wifiCount == 0) {
    performWifiScan();
    return;
  }
  uint8_t pages = (wifiCount + RADIO_RESULTS_PER_PAGE - 1) / RADIO_RESULTS_PER_PAGE;
  wifiPage = (wifiPage + 1) % pages;
  needsRender = true;
}
