# esphome-lora-radiolib

# 📡 ESPHome LoRa SX127x Component (via RadioLib)

A reliable and up-to-date ESPHome external component for LoRa SX1278/SX1276 modules. This component is built on top of the robust and highly maintained [RadioLib](https://github.com/jgromes/RadioLib) library (v6.3.0) to solve the issue of deprecated or broken LoRa custom components in the ESPHome ecosystem.

## ✨ Features
* **Stable & Modern:** Uses the latest `RadioLib` framework fully compatible with modern ESP-IDF and Arduino cores.
* **Plug & Play:** No need to manually download or manage C++ files. Just use `external_components` in your YAML.
* **Hardware Support:** Tested working perfectly with ESP32 boards (including modern variants like ESP32-C3).
* 
---

# 🇹🇭 รายละเอียดภาษาไทย

คอมโพเนนต์เสริม (External Component) สำหรับเชื่อมต่อโมดูล **LoRa SX127x (เช่น SX1278)** เข้ากับระบบ **ESPHome** โดยพัฒนาต่อยอดจากไลบรารีมาตรฐาน `RadioLib` เวอร์ชันล่าสุด (6.3.0) 

โปรเจกต์นี้ถูกสร้างขึ้นเพื่อแก้ปัญหาโค้ด LoRa บน ESPHome รุ่นเก่าที่ไม่สามารถคอมไพล์ผ่าน หรือลิงก์ต้นทางถูกลบไปแล้ว ช่วยให้นักพัฒนาและผู้สนใจด้าน IoT สามารถดึงไปใช้งานได้ทันทีอย่างเสถียร

## ✨ จุดเด่น
* **ติดตั้งง่าย:** ดึงไลบรารีอัตโนมัติ ไม่ต้องสร้างไฟล์ C++ เองให้ยุ่งยาก แค่เรียกใช้ผ่าน YAML
* **รองรับฮาร์ดแวร์ใหม่ๆ:** ใช้งานได้กับบอร์ดตระกูล ESP32 รวมถึงรุ่นใหม่ๆ อย่าง **ESP32-C3** * **ปรับแต่งสะดวก:** สามารถกำหนดขา GPIO และความถี่คลื่นได้ตามต้องการผ่านไฟล์ YAML

## 🛠️ การต่อสาย (Wiring Diagram)
ตัวอย่างการต่อสายสำหรับโมดูล LoRa SX1278 ร่วมกับ ESP32-C3:

| ขาของ LoRa SX1278 | ขาของ ESP32-C3 | คำอธิบาย |
| :---: | :---: | :--- |
| VCC | 3.3V | แหล่งจ่ายไฟ (ห้ามต่อ 5V เด็ดขาด) |
| GND | GND | กราวด์ |
| SCK | GPIO 4 | ขาสัญญาณนาฬิกา (SPI Clock) |
| MISO | GPIO 5 | ขารับข้อมูล (SPI MISO) |
| MOSI | GPIO 6 | ขาส่งข้อมูล (SPI MOSI) |
| NSS / CS | GPIO 7 | เลือกชิป (Chip Select) |
| DIO0 | GPIO 3 | ขาสัญญาณขัดจังหวะ (Interrupt) |
| RST | GPIO 10 | ขารีเซ็ตโมดูล |

> **⚠️ ข้อควรระวัง:** กรุณาต่อเสาอากาศ (Antenna) เข้ากับโมดูล LoRa ก่อนจ่ายไฟเข้าวงจรเสมอ เพื่อป้องกันความเสียหายต่อชิปภาคส่งวิทยุ

---
**พัฒนาเพื่อสนับสนุนการศึกษาด้าน IoT และชุมชน Open Source**
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


