# Pocket Scout ESP32-S3-ePaper-1.54

Pocket Scout is Arduino firmware for the Waveshare ESP32-S3-ePaper-1.54 with touchscreen. It turns
the small e-paper board into a pocket electronics scout: system
stats, passive Wi-Fi and BLE scans, I2C discovery, internal sensor logging, GPIO pin
reference, low-power sleep, and status LED feedback.

![Waveshare ESP32-S3-ePaper-1.54](https://www.waveshare.com/img/devkit/ESP32-S3-ePaper-1.54/ESP32-S3-ePaper-1.54-details-1.jpg)

Official hardware pages:

- Product page: <https://www.waveshare.com/esp32-s3-epaper-1.54.htm>
- Wiki: <https://docs.waveshare.com/ESP32-S3-ePaper-1.54>
- Waveshare demo repo: <https://github.com/waveshareteam/ESP32-S3-ePaper-1.54>

## Hardware

The retail board is the Waveshare ESP32-S3-ePaper-1.54. During upload it
identifies as an ESP32-S3-PICO-1 with 8MB embedded flash and 8MB embedded PSRAM.

## Features

- 200 x 200 e-paper UI for the ESP32-S3-ePaper-1.54.
- Home page with time, date, temperature, humidity, and battery voltage.
- System page with free RAM, low RAM, sleep timeout, radio state, and internal sensors.
- Passive Wi-Fi scanner showing SSID, RSSI, channel, and security.
- Passive BLE scanner showing one advertisement per page.
- I2C scanner for onboard and connected devices.
- Sensor log with date, time, temperature, relative humidity, and voltage.
- GPIO pin reference.
- Touchscreen navigation for page changes and page actions.
- Deep sleep after idle for 2 minutes.
- GP3 green LED blink feedback for wake, page changes, actions, and sleep.

## Controls

- Short BOOT press: next page.
- Long BOOT press: action for the current page.
- Short touch on the display: next page.
- Long touch on the display: action for the current page.
- Long PWR press while awake: go to sleep.
- Press PWR to wake from deep sleep.

On pages with multiple result pages, long BOOT or a long display touch advances
to the next result page.

## Safety

The Wi-Fi page only performs normal scan-only discovery. It does not connect,
capture traffic, collect credentials or deauthenticate clients.

The BLE page only scans advertisements. The firmware does not connect to devices.

## Repository Layout

```text
firmware/PocketScout/                 Pocket Scout Arduino sketch
third_party/waveshare_epaper_display/ Minimal Waveshare display driver copy
LICENSE                               MIT license for Pocket Scout code
THIRD_PARTY.md                        Third-party code and license notes
```

Only two Waveshare files are copied because they are required for the current
firmware to compile:

- `epaper_driver_bsp.h`
- `epaper_driver_bsp.cpp`

The full Waveshare example repository is not included, but can be found in the link above.

## Build With Arduino CLI

Install Arduino CLI, then install the Espressif ESP32 board package.

### Windows PowerShell

Install Arduino CLI with Winget:

```powershell
winget install ArduinoSA.CLI
```

Close and reopen PowerShell, then verify the install:

```powershell
arduino-cli version
```

```powershell
arduino-cli config init
arduino-cli config add board_manager.additional_urls https://espressif.github.io/arduino-esp32/package_esp32_index.json
arduino-cli core update-index
arduino-cli core install esp32:esp32
```

Compile the firmware from the repository root:

```powershell
arduino-cli compile --fqbn "esp32:esp32:esp32s3:CDCOnBoot=cdc,PartitionScheme=huge_app,PSRAM=opi,FlashMode=qio,FlashSize=4M,USBMode=hwcdc,UploadMode=default,UploadSpeed=921600,CPUFreq=240,DebugLevel=none,EraseFlash=none" firmware/PocketScout
```

List connected boards and ports:

```powershell
arduino-cli board list
```

Find the upload port from the `Port` column. On Windows it usually looks like
`COM3`, `COM8`, or similar.

If multiple boards are connected, unplug the ESP32-S3-ePaper board, run the
command once, plug it back in, and run it again. The new port is the one to use
as `<PORT>` in the upload command.

Upload, replacing `<PORT>` with your board's serial port:

```powershell
arduino-cli upload -p <PORT> --fqbn "esp32:esp32:esp32s3:CDCOnBoot=cdc,PartitionScheme=huge_app,PSRAM=opi,FlashMode=qio,FlashSize=4M,USBMode=hwcdc,UploadMode=default,UploadSpeed=921600,CPUFreq=240,DebugLevel=none,EraseFlash=none" firmware/PocketScout
```

### Linux Bash

Install Arduino CLI with the official install script:

```bash
curl -fsSL https://raw.githubusercontent.com/arduino/arduino-cli/master/install.sh | sh
sudo install -m 0755 bin/arduino-cli /usr/local/bin/arduino-cli
```

Verify the install:

```bash
arduino-cli version
```

```bash
arduino-cli config init
arduino-cli config add board_manager.additional_urls https://espressif.github.io/arduino-esp32/package_esp32_index.json
arduino-cli core update-index
arduino-cli core install esp32:esp32
```

Compile the Pocket Scout from the repository root:

```bash
arduino-cli compile --fqbn "esp32:esp32:esp32s3:CDCOnBoot=cdc,PartitionScheme=huge_app,PSRAM=opi,FlashMode=qio,FlashSize=4M,USBMode=hwcdc,UploadMode=default,UploadSpeed=921600,CPUFreq=240,DebugLevel=none,EraseFlash=none" firmware/PocketScout
```

List connected boards and ports:

```bash
arduino-cli board list
```

Find the upload port from the `Port` column. On Linux it is often
`/dev/ttyACM0` or `/dev/ttyUSB0`.

If multiple boards are connected, unplug the ESP32-S3-ePaper board, run the
command once, plug it back in, and run it again. The new port is the one to use
as `<PORT>` in the upload command.

Upload, replacing `<PORT>` with your board's serial port:

```bash
arduino-cli upload -p <PORT> --fqbn "esp32:esp32:esp32s3:CDCOnBoot=cdc,PartitionScheme=huge_app,PSRAM=opi,FlashMode=qio,FlashSize=4M,USBMode=hwcdc,UploadMode=default,UploadSpeed=921600,CPUFreq=240,DebugLevel=none,EraseFlash=none" firmware/PocketScout
```

Known working board options:

- Board profile: `ESP32S3 Dev Module`
- USB CDC on boot: enabled
- USB mode: hardware CDC and JTAG
- Partition scheme: huge app
- PSRAM: OPI
- Flash mode: QIO
- Flash size: 4MB
- CPU frequency: 240 MHz
- Upload speed: 921600

The V2 board reports 8MB flash and 8MB PSRAM, but this project has been tested
with the 4MB flash-size Arduino setting above.

## Build With Arduino IDE

1. Install Arduino IDE 2.x.
2. Open Preferences.
3. Add this Additional Boards Manager URL:

   ```text
   https://espressif.github.io/arduino-esp32/package_esp32_index.json
   ```

4. Open Boards Manager and install `esp32` by Espressif Systems.
5. Open `firmware/PocketScout/PocketScout.ino`.
6. Select board `ESP32S3 Dev Module`.
7. Set the board options to match the CLI settings:
   - USB CDC On Boot: enabled
   - USB Mode: hardware CDC and JTAG
   - Partition Scheme: huge app
   - PSRAM: OPI
   - Flash Mode: QIO
   - Flash Size: 4MB
   - CPU Frequency: 240 MHz
   - Upload Speed: 921600
8. Use Verify to compile.
9. Select the board's serial port.
10. Use Upload.

## ESP-IDF

The Waveshare board supports ESP-IDF, but Pocket Scout is currently an Arduino
sketch. It uses Arduino APIs such as `setup()`, `loop()`, `Arduino.h`, `WiFi`,
`BLEDevice`, `Preferences`, and `Wire`.

This repository does not currently include an ESP-IDF project and does not build
with `idf.py`. An ESP-IDF version would require either an Arduino-as-component
project wrapper or a native ESP-IDF port.

## License

Pocket Scout firmware is licensed under the MIT License. See `LICENSE`.

The Waveshare display driver files under `third_party/` are third-party files.
See `THIRD_PARTY.md`.
