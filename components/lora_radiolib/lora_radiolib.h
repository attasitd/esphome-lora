#pragma once
#include "esphome/core/component.h"
#include "esphome/core/log.h"
#include "esphome/components/text_sensor/text_sensor.h"
#include <SPI.h>
#include <RadioLib.h>

namespace esphome {
namespace lora_radiolib {

// คลาสนี้เป็น TextSensor แล้ว!
class LoRaRadioLib : public text_sensor::TextSensor, public Component {
 public:
  void set_pins(int cs, int dio0, int rst) {
    cs_ = cs; dio0_ = dio0; rst_ = rst;
  }
  void set_frequency(float freq) { freq_ = freq; }

  void setup() override {
    ESP_LOGD("lora_radiolib", "Starting LoRa RadioLib Component...");
    hal_ = new ArduinoHal(SPI);
    module_ = new Module(hal_, cs_, dio0_, rst_);
    radio_ = new SX1278(module_);

    int state = radio_->begin(freq_);
    if (state == RADIOLIB_ERR_NONE) {
      ESP_LOGD("lora_radiolib", "LoRa Initialize Success!");
    } else {
      ESP_LOGE("lora_radiolib", "LoRa Failed, code: %d", state);
      mark_failed(); 
    }
  }

  void loop() override {
    String str;
    int state = radio_->receive(str);
    if (state == RADIOLIB_ERR_NONE) {
      ESP_LOGI("lora_radiolib", "Received packet: %s", str.c_str());
      
      // 🚀 คำสั่งนี้แหละครับที่จะโยนข้อความขึ้นหน้า Home Assistant!
      this->publish_state(str.c_str());
    }
  }

 protected:
  int cs_, dio0_, rst_;
  float freq_;
  ArduinoHal* hal_;
  Module* module_;
  SX1278* radio_;
};

}  // namespace lora_radiolib
}  // namespace esphome
