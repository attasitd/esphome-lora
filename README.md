# 📡 ESPHome LoRa Component (Simple & Reliable)

A lightweight and highly compatible ESPHome external component for LoRa SX127x modules. This component is built using the well-known [sandeepmistry/LoRa](https://github.com/sandeepmistry/arduino-LoRa) library to ensure maximum stability and ease of use within the ESPHome ecosystem.

## ✨ Features
* **High Compatibility:** Uses the industry-standard `LoRa.h` library, ensuring it works with most LoRa gateways and transmitters.
* **Advanced Tuning:** Now supports custom Spreading Factor (SF), TX Power, and Coding Rate (CR) directly from YAML.
* **Plug & Play:** Automatically handles library dependencies. Just add the repository to your YAML.
* **RSSI Monitoring:** Built-in signal strength (RSSI) logging for easy antenna tuning.
* **Text Sensor Integration:** Received data is automatically published as a `text_sensor` in Home Assistant.

---

# 🇹🇭 รายละเอียดภาษาไทย

คอมโพเนนต์เสริม (External Component) สำหรับเชื่อมต่อโมดูล **LoRa SX127x (เช่น SX1278)** เข้ากับระบบ **ESPHome** โดยพัฒนาจากไลบรารีมาตรฐาน `LoRa.h` (Sandeep Mistry) ที่ขึ้นชื่อเรื่องความเสถียรและใช้งานง่ายที่สุด

โปรเจกต์นี้ถูกสร้างขึ้นเพื่อเป็นทางเลือกที่ "เรียบง่ายและใช้งานได้จริง" สำหรับนักพัฒนา IoT และนักศึกษาที่ต้องการส่งข้อมูลไร้สายระยะไกลเข้าสู่ระบบ Home Assistant

## ✨ จุดเด่น
* **เสถียรสูง:** ใช้ไลบรารีมาตรฐานที่ผ่านการทดสอบมาอย่างยาวนาน
* **ปรับแต่งได้ละเอียด:** รองรับการตั้งค่า Spreading Factor, กำลังส่ง (TX Power) และ Coding Rate ผ่าน YAML ได้ทันที
* **พร้อมใช้งานทันที:** ไม่ต้องตั้งค่าไลบรารีเอง ระบบจะดึงข้อมูลที่จำเป็นมาติดตั้งให้โดยอัตโนมัติ
* **แสดงผลเรียลไทม์:** ข้อมูลที่ได้รับจะแสดงใน Log พร้อมค่าความแรงสัญญาณ (RSSI) และส่งเข้า Home Assistant ทันที

## 🛠️ การต่อสาย (Wiring Diagram)
ตัวอย่างการต่อสายสำหรับโมดูล LoRa SX1278 ร่วมกับ ESP32-C3:

| ขาของ LoRa SX1278 | ขาของ ESP32-C3 | คำอธิบาย |
| :---: | :---: | :--- |
| **VCC** | 3.3V | แหล่งจ่ายไฟ (ห้ามต่อ 5V เด็ดขาด) |
| **GND** | GND | กราวด์ |
| **SCK** | GPIO 4 | SPI Clock |
| **MISO** | GPIO 5 | SPI MISO |
| **MOSI** | GPIO 6 | SPI MOSI |
| **NSS / CS** | GPIO 7 | Chip Select |
| **DIO0** | GPIO 3 | Interrupt Pin |
| **RST** | GPIO 10 | Reset Pin |

> **⚠️ ข้อควรระวัง:** กรุณาต่อเสาอากาศ (Antenna) ก่อนจ่ายไฟเข้าโมดูลเสมอ เพื่อป้องกันภาคส่งวิทยุเสียหาย

---

## 🚀 Installation & Usage

Add the following configuration to your `esphome.yaml` file:

```yaml
external_components:
  - source:
      type: git
      url: [https://github.com/attasitd/esphome-lora](https://github.com/attasitd/esphome-lora)
    refresh: 0s

# Define SPI bus pins
spi:
  clk_pin: GPIO4
  mosi_pin: GPIO6
  miso_pin: GPIO5

# Configure the LoRa receiver
lora_simple:
  id: my_lora
  name: "LoRa Received Data"
  cs_pin: 7
  dio0_pin: 3
  rst_pin: 10
  frequency: 433.0        # Set frequency in MHz
  
  # Advanced Settings (Optional)
  tx_power: 17            # 2 to 20 dBm (Default: 17)
  spreading_factor: 7     # 6 to 12 (Default: 7)
  coding_rate: 5          # 5 to 8 for 4/5-4/8 (Default: 5)
```
📝 Change Log (อัปเดตล่าสุด)

เพิ่มฟังก์ชัน set_sync_word() และ set_bandwidth() เพื่อรองรับการรับข้อมูลจากบอร์ด Arduino ที่ใช้ค่าเจาะจง

เพิ่มฟังก์ชัน get_rssi() และ get_snr() สำหรับการทำ Dashboard บนหน้าจอ OLED

ปรับปรุงไฟล์ __init__.py ให้รองรับการตรวจสอบค่าผ่าน YAML Validator ของ ESPHome
