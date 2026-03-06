# esphome-lora-radiolib

# 📡 ESPHome LoRa SX127x Component (via RadioLib)

A reliable and up-to-date ESPHome external component for LoRa SX1278/SX1276 modules. This component is built on top of the robust and highly maintained [RadioLib](https://github.com/jgromes/RadioLib) library (v6.3.0) to solve the issue of deprecated or broken LoRa custom components in the ESPHome ecosystem.

## ✨ Features
* **Stable & Modern:** Uses the latest `RadioLib` framework fully compatible with modern ESP-IDF and Arduino cores.
* **Plug & Play:** No need to manually download or manage C++ files. Just use `external_components` in your YAML.
* **Hardware Support:** Tested working perfectly with ESP32 boards (including modern variants like ESP32-C3).
* 
LoRa SX1278 Pin,ESP32-C3 Pin,Description
VCC,3.3V,Power Supply (ห้ามต่อ 5V เด็ดขาด)
GND,GND,Ground
SCK,GPIO 4,SPI Clock
MISO,GPIO 5,SPI MISO
MOSI,GPIO 6,SPI MOSI
NSS / CS,GPIO 7,Chip Select
DIO0,GPIO 3,Interrupt Pin
RST,GPIO 10,Reset Pin
## 🚀 Installation & Usage

Add the following configuration to your `esphome.yaml` file. Make sure to adjust the pins and frequency according to your specific hardware setup.

```yaml
# 1. Import the component from this repository
external_components:
  - source:
      type: git
      url: [https://github.com/attasitd/esphome-lora-radiolib](https://github.com/attasitd/esphome-lora-radiolib)
    refresh: 1h

# 2. Define the hardware SPI pins
spi:
  clk_pin: GPIO4
  mosi_pin: GPIO6
  miso_pin: GPIO5

# 3. Configure the LoRa module
lora_radiolib:
  cs_pin: 7
  dio0_pin: 3
  rst_pin: 10
  frequency: 433.0  # Change to 915.0 or 868.0 if required

