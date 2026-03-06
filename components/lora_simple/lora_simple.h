#pragma once
#include "esphome/core/component.h"
#include "esphome/core/log.h"
#include "esphome/components/text_sensor/text_sensor.h"
#include <SPI.h>
#include <LoRa.h>

namespace esphome {
namespace lora_simple {

class LoRaComponent : public text_sensor::TextSensor, public Component {
 public:
  void set_pins(int cs, int dio0, int rst) {
    cs_ = cs; dio0_ = dio0; rst_ = rst;
  }
  void set_frequency(float freq) { freq_ = freq; }

  // 🚀 ฟังก์ชันใหม่สำหรับ "ส่งข้อมูล" กลับไป
  void send_data(std::string message) {
    ESP_LOGI("lora", "Sending LoRa packet: %s", message.c_str());
    LoRa.beginPacket();
    LoRa.print(message.c_str());
    LoRa.endPacket();
    
    // สำคัญ: หลังจากส่งเสร็จ ต้องกลับมาโหมดรับ (Listen) เหมือนเดิม
    LoRa.receive(); 
  }

  void setup() override {
    ESP_LOGD("lora", "Starting LoRa Simple Component...");
    LoRa.setPins(cs_, rst_, dio0_);
    if (!LoRa.begin(freq_ * 1E6)) {
      ESP_LOGE("lora", "LoRa Init Failed!");
      mark_failed();
      return;
    }
    LoRa.receive(); // เริ่มต้นในโหมดรอรับ
    ESP_LOGD("lora", "LoRa Init Success!");
  }

  void loop() override {
    int packetSize = LoRa.parsePacket();
    if (packetSize) {
      std::string data = "";
      while (LoRa.available()) {
        data += (char)LoRa.read();
      }
      ESP_LOGI("lora", "Received: %s | RSSI: %d", data.c_str(), LoRa.packetRssi());
      this->publish_state(data);
    }
  }

 protected:
  int cs_, dio0_, rst_;
  float freq_;
};

}  // namespace lora_simple
}  // namespace esphome
