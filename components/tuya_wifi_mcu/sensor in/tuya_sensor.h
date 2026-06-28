#pragma once

#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
#include "../tuya_wifi_mcu_entity.h" 

namespace esphome {
namespace tuya_wifi_mcu {

class TuyaSensor : public sensor::Sensor, public Component, public TuyaWiFiMCUEntity {
 public:
  void setup() override;
  void process_dp_data(const uint8_t *value, size_t length) override;
};

}  // namespace tuya_wifi_mcu
}  // namespace esphome