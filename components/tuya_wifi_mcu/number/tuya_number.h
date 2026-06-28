#pragma once
#include "esphome.h"
#include "esphome/core/component.h"
#include "esphome/components/number/number.h"

#include "../tuya_wifi_mcu_entity.h"

namespace esphome {
  namespace tuya_wifi_mcu {
    class TuyaWifiMcuNumber : public TuyaWifiMcuEntity, public Component, public number::Number {
    public:
      void set_dp_id(uint8_t dp_id) { this->dp_id_ = dp_id; };
      
      // เพิ่มฟังก์ชันสำหรับผูก (Bind) เข้ากับ Number ตัวอื่นใน HA
      void set_bind_number(number::Number* bind_number) { 
        this->is_bind_ = true;
        this->bind_number_ = bind_number;
      };

      uint8_t get_dp_type() override { return DP_TYPE_VALUE; };
      void setup() override;
      void dump_config() override;
      void process_dp_data(const unsigned char value[], unsigned short length) override;
      void report_tuya_dp_state() override;

    protected:
      void control(float value) override; // ฟังก์ชันรับค่าจาก HA ไปสั่ง Tuya
      
      bool is_bind_ = false;
      number::Number* bind_number_ = nullptr;
    };
  }
}