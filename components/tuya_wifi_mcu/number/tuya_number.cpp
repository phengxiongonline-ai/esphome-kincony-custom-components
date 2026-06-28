#include "tuya_number.h"
#include "esphome/core/log.h"

namespace esphome {
namespace tuya_wifi_mcu {

static const char *const TAG = "tuya.number";

void TuyaNumber::setup() {
  // บอร์ดเปิดตัวมารอรับสายสัญญาณนิ่งๆ
}

// 🔵 ระบบรับค่าเข้ามาอ่านโชว์บนจอ Home Assistant
void TuyaNumber::process_dp_data(const uint8_t *value, size_t length) {
  if (length < 1) return;
  
  uint32_t val = 0;
  for (size_t i = 0; i < length; i++) {
    val = (val << 8) | value[i];
  }
  
  ESP_LOGD(TAG, "ได้รับสถานะตัวเลขจาก Tuya DP [%d] -> ค่าคือ: %d", this->dpid_, val);
  this->publish_state(val); 
}

// 🔴 ระบบส่งเขียนค่าออกไปสั่งชิป Tuya ยิงผ่านพอร์ตกลางอัตโนมัติ
void TuyaNumber::control(float value) {
  this->publish_state(value);
  uint32_t val = (uint32_t)value;

  ESP_LOGD(TAG, "กำลังส่งตั้งค่าตัวเลขใหม่ไป Tuya DP [%d] -> สั่งค่า: %d", this->dpid_, val);

  // เตรียมชุดไบต์รหัสตามมาตรฐานข้อมูลประเภท Value (ตัวเลข 4 ไบต์)
  uint8_t data[4];
  data[0] = (val >> 24) & 0xFF;
  data[1] = (val >> 16) & 0xFF;
  data[2] = (val >> 8) & 0xFF;
  data[3] = val & 0xFF;

  // วิ่งไปเคาะประตูเรียกฟังก์ชันส่งดั้งเดิมหลังบ้านของบอร์ดแม่ให้จัดการยิง Hex ออกสายซีเรียลทันที
  this->parent_->mcu_dp_update(this->dpid_, data, 4); 
}

}  // namespace tuya_wifi_mcu
}  // namespace esphome