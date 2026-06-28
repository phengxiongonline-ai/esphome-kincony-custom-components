import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor
from .. import tuya_wifi_mcu_ns, TuyaWifiMcuEntity

TuyaWifiMcuSensor = tuya_wifi_mcu_ns.class_("TuyaWifiMcuSensor", sensor.Sensor, cg.Component, TuyaWifiMcuEntity)

CONFIG_SCHEMA = sensor.sensor_schema(TuyaWifiMcuSensor).extend({
    cv.Required("dp_id"): cv.int_,
    # เพิ่มตัวเลือกสำหรับใส่ ID ของ Sensor ที่ต้องการ Bind
    cv.Optional("bind_id"): cv.use_id(sensor.Sensor),
}).extend(cv.COMPONENT_SCHEMA)

async def to_code(config):
    var = await sensor.new_sensor(config)
    await cg.register_component(var, config)
    cg.add(var.set_dp_id(config["dp_id"]))
    
    # ถ้ามีการกำหนด bind_id ให้ทำความรู้จักกันในระดับโค้ด C++
    if "bind_id" in config:
        bind_sensor = await cg.get_variable(config["bind_id"])
        cg.add(var.set_bind_sensor(bind_sensor))