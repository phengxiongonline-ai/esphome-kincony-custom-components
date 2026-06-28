#include "tuya_number.h"

namespace esphome {
  namespace tuya_wifi_mcu {
    void TuyaWifiMcuNumber::setup() {
      ESP_LOGD("tuya.number", "Setup DP: %d, is_bind: %d", dp_id_, is_bind_);

      // ถ้ามีการ Bind ให้ดักฟังการเปลี่ยนแปลงสถานะเพื่อซิงค์
      this->add_on_state_callback([this](float state) {
        if (this->is_bind_) {
          this->bind_number_->publish_state(state);
        }
      });

      if (this->is_bind_) {
        this->bind_number_->add_on_state_callback([this](float state) {
          this->publish_state(state);
        });
      }
    }

    void TuyaWifiMcuNumber::dump_config() {
      ESP_LOGCONFIG("tuya.number", "Tuya Number DP: %d, is_bind: %d", dp_id_, is_bind_);
    }

    void TuyaWifiMcuNumber::control(float value) {
      if (this->tuya_wifi_ != nullptr) {
        // ส่งคำสั่งงานกลับไปที่ Tuya MCU (4 ไบต์)
        this->tuya_wifi_->mcu_dp_update(this->dp_id_, (int)value, 4);
        this->publish_state(value); // อัปเดตสถานะหน้าจอ HA
      }
    }

    void TuyaWifiMcuNumber::process_dp_data(const unsigned char value[], unsigned short length) {
      // แปลงข้อมูลไบต์กลับเป็นตัวเลข ( float)
      auto val = this->tuya_wifi_->mcu_get_dp_download_data(this->dp_id_, value, length);
      this->publish_state((float)val);
    }

    void TuyaWifiMcuNumber::report_tuya_dp_state() {
      // รายงานสถานะปัจจุบันกลับไปที่ Tuya MCU
      this->tuya_wifi_->mcu_dp_update(this->dp_id_, (int)this->state, 4);
    }
  }
}