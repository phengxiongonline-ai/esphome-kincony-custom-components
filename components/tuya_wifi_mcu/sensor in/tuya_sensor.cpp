#include "tuya_sensor.h"
#include "esphome/core/log.h"

namespace esphome {
namespace tuya_wifi_mcu {

static const char *const TAG = "tuya.sensor";

void TuyaSensor::setup() {
  
}

void TuyaSensor::process_dp_data(const uint8_t *value, size_t length) {
  if (length < 1) return;
  
  uint32_t raw_value = 0;
  for (size_t i = 0; i < length; i++) {
    raw_value = (raw_value << 8) | value[i];
  }
  
  float final_value = (float)raw_value;
  ESP_LOGD(TAG, "sensor data decoded -> DP [%d] = %.2f", this->dpid_, final_value);
  
  this->publish_state(final_value);
}

}  // namespace tuya_wifi_mcu
}  // namespace esphome