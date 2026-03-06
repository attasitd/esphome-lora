# esphome-lora-radiolib

# 📡 ESPHome LoRa SX127x Component (via RadioLib)

A reliable and up-to-date ESPHome external component for LoRa SX1278/SX1276 modules. This component is built on top of the robust and highly maintained [RadioLib](https://github.com/jgromes/RadioLib) library (v6.3.0) to solve the issue of deprecated or broken LoRa custom components in the ESPHome ecosystem.

## ✨ Features
* **Stable & Modern:** Uses the latest `RadioLib` framework fully compatible with modern ESP-IDF and Arduino cores.
* **Plug & Play:** No need to manually download or manage C++ files. Just use `external_components` in your YAML.
* **Hardware Support:** Tested working perfectly with ESP32 boards (including modern variants like ESP32-C3).

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


คอมโพเนนต์เสริม (External Component) สำหรับเชื่อมต่อโมดูล LoRa SX127x (เช่น SX1278) เข้ากับระบบ ESPHome โดยพัฒนาต่อยอดจากไลบรารีมาตรฐาน RadioLib เวอร์ชันล่าสุด (6.3.0)โปรเจกต์นี้ถูกสร้างขึ้นเพื่อแก้ปัญหาโค้ด LoRa บน ESPHome รุ่นเก่าที่ไม่สามารถคอมไพล์ผ่าน หรือลิงก์ต้นทางถูกลบไปแล้ว ช่วยให้นักพัฒนาและผู้สนใจด้าน IoT สามารถดึงไปใช้งานได้ทันทีอย่างเสถียร✨ จุดเด่นดึงไลบรารีอัตโนมัติ ไม่ต้องสร้างไฟล์ C++ เองให้ยุ่งยากรองรับบอร์ดตระกูล ESP32 รวมถึงรุ่นใหม่ๆ อย่าง ESP32-C3 * ปรับเปลี่ยนขา GPIO และความถี่คลื่นได้ง่ายๆ ผ่านไฟล์ YAML🛠️ การต่อสาย (Wiring Diagram)ตัวอย่างการต่อสายสำหรับโมดูล LoRa SX1278 ร่วมกับ ESP32-C3:LoRa SX1278 PinESP32-C3 PinDescriptionVCC3.3VPower Supply (ห้ามต่อ 5V เด็ดขาด)GNDGNDGroundSCKGPIO 4SPI ClockMISOGPIO 5SPI MISOMOSIGPIO 6SPI MOSINSS / CSGPIO 7Chip SelectDIO0GPIO 3Interrupt PinRSTGPIO 10Reset Pin(หมายเหตุ: อย่าลืมต่อเสาอากาศก่อนจ่ายไฟเข้าโมดูลเสมอ เพื่อป้องกันชิปวิทยุเสียหาย)Developed for IoT Education & Open Source Community. ```💡 วิธีนำไปใช้:เข้าไปที่หน้า Repository ของอาจารย์ (https://github.com/attasitd/esphome-lora-radiolib)ถ้าอาจารย์สร้างไฟล์ README.md ไว้แล้ว ให้กดที่ไอคอนรูป ดินสอ ✏️ (Edit) ที่มุมขวาบนของไฟล์วางโค้ดทั้งหมดที่ผมให้ไว้ทับลงไปกดปุ่ม Commit changes... สีเขียวได้เลยครับพออัปเดตเสร็จ หน้า GitHub ของอาจารย์จะดูสวยงามและอ่านง่ายมากๆ ครับ หวังว่าโปรเจกต์นี้จะเป็นประโยชน์ทั้งกับงานสอนในห้องเรียน และกับผู้ใช้ Home Assistant ทั่วโลกเลยนะครับ!ถ้าอาจารย์สร้างเสร็จเรียบร้อยและคอมไพล์ฝั่งตัวรับที่บ้านผ่านแล้ว จะให้ผมช่วยเขียนโค้ดสำหรับฝั่ง "ตัวส่ง" เพื่อเตรียมรับข้อมูลความชื้นจากสวนปาล์มต่อเลยไหมครับ?
