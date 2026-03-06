#pragma once
#include "esphome/core/component.h"
#include "esphome/core/log.h"
#include "esphome/components/text_sensor/text_sensor.h"
#include <SPI.h>
#include <LoRa.h>

namespace esphome {
namespace lora_radiolib {

class LoRaRadioLib : public text_sensor::TextSensor, public Component {
 public:
  // ฟังก์ชันรับค่าจาก Python (__init__.py)
  void set_pins(int cs, int dio0, int rst) {
    cs_ = cs; dio0_ = dio0; rst_ = rst;
  }
  
  void set_frequency(float freq) {
    freq_ = freq;
  }

  void setup() override {
    ESP_LOGD("lora", "Starting LoRa (Sandeep Mistry Library)...");
    
    // ตั้งค่าขาสัญญาณ
    LoRa.setPins(cs_, rst_, dio0_);

    // เริ่มต้นทำงานตามความถี่ที่กำหนด (หน่วยเป็น Hz)
    if (!LoRa.begin(freq_ * 1E6)) {
      ESP_LOGE("lora", "Starting LoRa failed! Check wiring.");
      mark_failed();
      return;
    }
    
    ESP_LOGD("lora", "LoRa Initialize Success! Frequency: %.1f MHz", freq_);
  }

  void loop() override {
    // ตรวจสอบว่ามีข้อมูลส่งมาหรือไม่
    int packetSize = LoRa.parsePacket();
    
    if (packetSize) {
      std::string data = "";
      while (LoRa.available()) {
        data += (char)LoRa.read();
      }
      
      // แสดงผลใน Log ของ ESPHome (สีเขียว/ฟ้า)
      ESP_LOGI("lora", "Received: %s | RSSI: %d dBm", data.c_str(), LoRa.packetRssi());
      
      // 🚀 ส่งข้อมูลเข้า Home Assistant เป็น Text Sensor
      this->publish_state(data);
    }
  }

 protected:
  int cs_, dio0_, rst_;
  float freq_ = 433.0; // ค่าเริ่มต้นถ้าไม่มีการกำหนด
};

}  // namespace lora_radiolib
}  // namespace esphome
