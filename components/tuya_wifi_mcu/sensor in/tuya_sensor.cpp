#include "tuya_sensor.h"

namespace esphome {
  namespace tuya_wifi_mcu {
    void TuyaWifiMcuSensor::setup() {
      ESP_LOGD("tuya.sensor", "Setup DP: %d, is_bind: %d", dp_id_, is_bind_);
      
      // ถ้ามีการ Bind ให้ซิงค์สถานะ
      this->add_on_state_callback([this](float state) {
        if (this->is_bind_) {
          this->bind_sensor_->publish_state(state);
        }
      });
      
      if (this->is_bind_) {
        this->bind_sensor_->add_on_state_callback([this](float state) {
          this->publish_state(state);
        });
      }
    }
    
    void TuyaWifiMcuSensor::dump_config() {
      ESP_LOGCONFIG("tuya.sensor", "Tuya Sensor DP: %d, is_bind: %d", dp_id_, is_bind_);
    }
    
    void TuyaWifiMcuSensor::process_dp_data(const unsigned char value[], unsigned short length) {
      // แปลงข้อมูลไบต์กลับเป็นตัวเลข (float)
      auto val = this->tuya_wifi_->mcu_get_dp_download_data(this->dp_id_, value, length);
      this->publish_state((float)val);
    }
    
    void TuyaWifiMcuSensor::report_tuya_dp_state() {
      // Sensor ส่วนใหญ่รับค่าอย่างเดียว แต่ต้องเขียนหัวฟังก์ชันไว้
    }
  }
}