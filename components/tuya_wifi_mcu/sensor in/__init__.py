import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor

tuya_ns = cg.esphome_ns.namespace("tuya_wifi_mcu")
TuyaSensor = tuya_ns.class_("TuyaSensor", sensor.Sensor, cg.Component)

CONF_ID = "id"
CONF_TUYA_WIFI_MCU_ID = "tuya_wifi_mcu_id"
CONF_TUYA_DP_ID = "tuya_dp_id"

CONFIG_SCHEMA = sensor.SENSOR_SCHEMA.extend({
    cv.GenerateID(): cv.declare_id(TuyaSensor),
    cv.Required(CONF_TUYA_WIFI_MCU_ID): cv.use_id(tuya_ns.class_("TuyaWiFiMCUComponent")),
    cv.Required(CONF_TUYA_DP_ID): cv.uint8_t,
}).extend(cv.COMPONENT_SCHEMA)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await sensor.register_sensor(var, config)
    
    cg.add(var.set_dp_id(config[CONF_TUYA_DP_ID]))
    
    parent = await cg.get_variable(config[CONF_TUYA_WIFI_MCU_ID])
    cg.add(parent.register_entity(var))