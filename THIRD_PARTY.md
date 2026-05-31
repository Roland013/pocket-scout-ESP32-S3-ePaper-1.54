# Third-Party Notices

Pocket Scout is MIT licensed, but not every file in this repository is Pocket
Scout code.

## Waveshare e-Paper Display Driver

Location:

```text
third_party/waveshare_epaper_display/
```

Files:

```text
epaper_driver_bsp.h
epaper_driver_bsp.cpp
```

Source:

```text
https://github.com/waveshareteam/ESP32-S3-ePaper-1.54
```

Original path:

```text
02_Example/Arduino/10_LVGL_V9_Test/src/display/
```

These two files are copied because they are the only Waveshare source files
required by the current Pocket Scout Arduino sketch. No license notice was found
in those files at the time of import. The project MIT license does not apply to
these Waveshare files.

## External Build Dependencies

These dependencies are installed through the Arduino ESP32 platform and are not
vendored in this repository:

- Arduino core for ESP32 by Espressif Systems
- ESP-IDF headers and libraries bundled with Arduino ESP32
- Arduino `WiFi`, `Wire`, `Preferences`, and BLE libraries
