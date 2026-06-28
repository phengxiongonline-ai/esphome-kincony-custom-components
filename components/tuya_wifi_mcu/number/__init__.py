import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import number
from .. import tuya_wifi_mcu_ns, TuyaWifiMcuEntity

TuyaWifiMcuNumber = tuya_wifi_mcu_ns.class_("TuyaWifiMcuNumber", number.Number, cg.Component, TuyaWifiMcuEntity)

CONFIG_SCHEMA = number.number_schema(TuyaWifiMcuNumber).extend({
    cv.Required("dp_id"): cv.int_,
    # เพิ่มตัวเลือกสำหรับใส่ ID ของ Number ที่ต้องการ Bind
    cv.Optional("bind_id"): cv.use_id(number.Number),
}).extend(cv.COMPONENT_SCHEMA)

async def to_code(config):
    var = await number.new_number(config, min_value=0, max_value=100, step= step)
    await cg.register_component(var, config)
    cg.add(var.set_dp_id(config["dp_id"]))
    
    # ถ้ามีการกำหนด bind_id ให้ทำความรู้จักกันในระดับโค้ด C++
    if "bind_id" in config:
        bind_number = await cg.get_variable(config["bind_id"])
        cg.add(var.set_bind_number(bind_number))