#pragma once
#include "esphome.h"
#include "esphome/components/sensor/sensor.h"
#include "../tuya_wifi_mcu_entity.h"

namespace esphome {
  namespace tuya_wifi_mcu {
    class TuyaWifiMcuSensor : public TuyaWifiMcuEntity, public Component, public sensor::Sensor {
    public:
      void set_dp_id(uint8_t dp_id) { this->dp_id_ = dp_id; };
      
      // เพิ่มฟังก์ชันสำหรับผูก (Bind) เข้ากับ Sensor ตัวอื่นใน HA
      void set_bind_sensor(sensor::Sensor* bind_sensor) { 
        this->is_bind_ = true;
        this->bind_sensor_ = bind_sensor;
      };

      uint8_t get_dp_type() override { return DP_TYPE_VALUE; };
      void setup() override;
      void dump_config() override;
      void process_dp_data(const unsigned char value[], unsigned short length) override;
      void report_tuya_dp_state() override;

    protected:
      bool is_bind_ = false;
      sensor::Sensor* bind_sensor_ = nullptr;
    };
  }
}