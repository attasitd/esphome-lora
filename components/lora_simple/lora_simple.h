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
  // ฟังก์ชัน Setter สำหรับรับค่าจาก Python
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
      mark_failed();
      return;
    }

    // สั่งงานชิปตามค่าที่ตั้งมา
    LoRa.setTxPower(tx_power_);
    LoRa.setSpreadingFactor(sf_);
    LoRa.setCodingRate4(cr_);
// บรรทัดที่ทำให้รับส่งได้ตรงกัน
    LoRa.setSyncWord(sw_);
    LoRa.setSignalBandwidth(bw_);    
    LoRa.receive(); 
    ESP_LOGI("lora", "LoRa Configured Successfully!");
  }

  // ... (ส่วน loop และ send_data เหมือนเดิม) ...
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
      // 1. แสดงผลใน Log (อาจารย์จะเห็นในหน้า ESPHome Logs ทันที)
      int rssi = LoRa.packetRssi();
      float snr = LoRa.packetSnr(); // แถมค่า SNR (คุณภาพสัญญาณ) ให้ด้วยครับ
      ESP_LOGI("lora", "Received: %s", data.c_str());
      ESP_LOGI("lora", "  -> RSSI: %d dBm", rssi);
      ESP_LOGI("lora", "  -> SNR: %.2f dB", snr);     
      this->publish_state(data);
    }
  }

 protected:
  int cs_, dio0_, rst_;
  float freq_;
  int tx_power_, sf_, cr_;
};

}  // namespace lora_simple
}  // namespace esphome
