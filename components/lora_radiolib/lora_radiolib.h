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
  void set_pins(int cs, int dio0, int rst) {
    cs_ = cs; rst_ = rst; dio0_ = dio0;
  }

  void setup() override {
    ESP_LOGD("lora", "Starting LoRa with sandeepmistry/LoRa...");
    
    // ตั้งค่าขาสัญญาณ
    LoRa.setPins(cs_, rst_, dio0_);

    // เริ่มต้นที่ความถี่ 433MHz
    if (!LoRa.begin(433E6)) {
      ESP_LOGE("lora", "Starting LoRa failed!");
      mark_failed();
      return;
    }
    ESP_LOGD("lora", "LoRa Initialize Success!");
  }

  void loop() override {
    // ตรวจสอบขนาดของ Packet ที่รับได้
    int packetSize = LoRa.parsePacket();
    if (packetSize) {
      std::string data = "";
      while (LoRa.available()) {
        data += (char)LoRa.read();
      }
      
      ESP_LOGI("lora", "Received: %s (RSSI: %d)", data.c_str(), LoRa.packetRssi());
      
      // ส่งค่าขึ้น Home Assistant
      this->publish_state(data);
    }
  }

 protected:
  int cs_, rst_, dio0_;
};

}  // namespace lora_radiolib
}  // namespace esphome
