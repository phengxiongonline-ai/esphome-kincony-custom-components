#pragma once

#include "esphome/core/component.h"
#include "esphome/components/number/number.h"
#include "../tuya_wifi_mcu_entity.h" // ดึงโครงสร้างเอ็นทิตี้สากลมาร่วมงาน

namespace esphome {
namespace tuya_wifi_mcu {

class TuyaNumber : public number::Number, public Component, public TuyaWiFiMCUEntity {
 public:
  void setup() override;
  
  // ขาเข้า: รับฟังค่าตัวเลขที่ชิป Tuya รายงานมา
  void process_dp_data(const uint8_t *value, size_t length) override; 

 protected:
  // ขาออก: สั่งงานตอนเรากดสไลเดอร์ตัวเลขบนหน้าจอ
  void control(float value) override; 
};

}  // namespace tuya_wifi_mcu
}  // namespace esphome