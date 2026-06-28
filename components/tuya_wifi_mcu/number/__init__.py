import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import number

# อ้างอิง Namespace ของคลัง Kincony หลัก
tuya_ns = cg.esphome_ns.namespace("tuya_wifi_mcu")
TuyaNumber = tuya_ns.class_("TuyaNumber", number.Number, cg.Component)

# กำหนดค่าคีย์เวิร์ดมาตรฐานเองโดยตรงเพื่อเลี่ยงการแจ้งเตือนของ VS Code
CONF_ID = "id"
CONF_TUYA_WIFI_MCU_ID = "tuya_wifi_mcu_id"
CONF_TUYA_DP_ID = "tuya_dp_id"

CONFIG_SCHEMA = number.NUMBER_SCHEMA.extend({
    cv.GenerateID(): cv.declare_id(TuyaNumber),
    cv.Required(CONF_TUYA_WIFI_MCU_ID): cv.use_id(tuya_ns.class_("TuyaWiFiMCUComponent")),
    cv.Required(CONF_TUYA_DP_ID): cv.uint8_t,
}).extend(cv.COMPONENT_SCHEMA)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    # ตั้งค่าสไลเดอร์ตัวเลข 0 ถึง 100 บนหน้าจอ
    await number.register_number(var, config, min_value=0, max_value=100, step=1)
    
    cg.add(var.set_dp_id(config[CONF_TUYA_DP_ID]))
    
    # ลงทะเบียนผูกกับระบบบอร์ดแม่ Kincony อัตโนมัติ
    parent = await cg.get_variable(config[CONF_TUYA_WIFI_MCU_ID])
    cg.add(parent.register_entity(var))