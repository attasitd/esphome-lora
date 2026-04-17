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
  // ฟังก์ชัน Setter สำหรับรับค่าจาก Python (__init__.py)
  void set_pins(int cs, int dio0, int rst) { cs_ = cs; dio0_ = dio0; rst_ = rst; }
  void set_frequency(float freq) { freq_ = freq; }
  void set_tx_power(int power) { tx_power_ = power; }
  void set_spreading_factor(int sf) { sf_ = sf; }
  void set_coding_rate(int cr) { cr_ = cr; }
  void set_sync_word(int sw) { sw_ = sw; }
  void set_bandwidth(long bw) { bw_ = bw; }

  void setup() override {
    ESP_LOGD("lora", "Starting LoRa with SF%d, CR4/%d, Power %ddBm", sf_, cr_, tx_power_);
    LoRa.setPins(cs_, rst_, dio0_);

    if (!LoRa.begin(freq_ * 1E6)) {
      ESP_LOGE("lora", "LoRa Init Failed!");
      this->mark_failed();
      return;
    }

    // สั่งงานชิปตามค่าที่ส่งมาจาก YAML
    LoRa.setTxPower(tx_power_);
    LoRa.setSpreadingFactor(sf_);
    LoRa.setCodingRate4(cr_);
    LoRa.setSyncWord(sw_);           // ใช้ค่า 0x34 ที่ส่งมา
    LoRa.setSignalBandwidth(bw_);    // ใช้ค่า 125000 ที่ส่งมา
    
    LoRa.receive(); 
    ESP_LOGI("lora", "LoRa Configured Successfully! Sync: 0x%02X, BW: %ld", sw_, bw_);
  }

  void send_data(std::string message) {
    LoRa.beginPacket();
    LoRa.print(message.c_str());
    LoRa.endPacket();
    LoRa.receive(); 
  }

  void loop() override {
    int packetSize = LoRa.parsePacket();
    if (packetSize) {
      std::string data = "";
      while (LoRa.available()) { data += (char)LoRa.read(); }
      
      int rssi = LoRa.packetRssi();
      float snr = LoRa.packetSnr();
      
      ESP_LOGI("lora", "Received: %s", data.c_str());
      ESP_LOGI("lora", "  -> RSSI: %d dBm", rssi);
      ESP_LOGI("lora", "  -> SNR: %.2f dB", snr);     
      
      this->publish_state(data);
    }
  }

 protected:
  // --- ประกาศตัวแปรเก็บค่าพารามิเตอร์ ---
  int cs_, dio0_, rst_;
  float freq_;
  int tx_power_, sf_, cr_, sw_; // เพิ่ม sw_ ตรงนี้
  long bw_;                     // เพิ่ม bw_ ตรงนี้
};

}  // namespace lora_simple
}  // namespace esphome
