import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import number
from esphome.const import CONF_ID
from .. import TuyaWifiMcuComponent
#define "TuyaWifiMcuNumber"
DEPENDENCIES = ['tuya_wifi_mcu']

tuya_wifi_mcu_ns = cg.esphome_ns.namespace('tuya_wifi_mcu')
tuyaWifiMcuNumber = tuya_wifi_mcu_ns.class_('TuyaWifiMcuNumber', number.Number, cg.Component)

CONFIG_SCHEMA = number.number_schema(tuyaWifiMcuNumber).extend({
    cv.GenerateID(): cv.declare_id(tuyaWifiMcuNumber),
    cv.GenerateID("tuya_wifi_mcu_id"): cv.use_id(TuyaWifiMcuComponent),
    cv.Required("dp_id"): cv.int_,
    cv.Optional("bind_number_id"): cv.use_id(number)
}).extend(cv.COMPONENT_SCHEMA)

def to_code(config):
    paren = yield cg.get_variable(config["tuya_wifi_mcu_id"])
    var = cg.new_Pvariable(config[CONF_ID])
    yield cg.register_component(var, config)
    yield number.register_number(var, config)
    cg.add(var.set_dp_id(config["dp_id"]))
    if "bind_number_id" in config:
        bind_number = yield cg.get_variable(config["bind_number_id"])
        cg.add(var.set_bind_number(bind_number))
    cg.add(paren.register_tuya_wifi_mcu_entity(var))
