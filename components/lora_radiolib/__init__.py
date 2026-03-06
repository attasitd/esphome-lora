import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import text_sensor
from esphome.const import CONF_ID, CONF_FREQUENCY # เพิ่ม CONF_FREQUENCY

DEPENDENCIES = ['spi']
AUTO_LOAD = ['text_sensor']

lora_ns = cg.esphome_ns.namespace('lora_radiolib')
LoRaRadioLib = lora_ns.class_('LoRaRadioLib', text_sensor.TextSensor, cg.Component)

CONF_CS_PIN = 'cs_pin'
CONF_DIO0_PIN = 'dio0_pin'
CONF_RST_PIN = 'rst_pin'

CONFIG_SCHEMA = text_sensor.text_sensor_schema(LoRaRadioLib).extend({
    cv.Required(CONF_CS_PIN): cv.int_,
    cv.Required(CONF_DIO0_PIN): cv.int_,
    cv.Required(CONF_RST_PIN): cv.int_,
    cv.Optional(CONF_FREQUENCY, default=433.0): cv.float_, # เพิ่มบรรทัดนี้กลับมา
}).extend(cv.COMPONENT_SCHEMA)

async def to_code(config):
    cg.add_library("sandeepmistry/LoRa", "0.8.0")
    var = cg.new_Pvariable(config[CONF_ID])
    
    await cg.register_component(var, config)
    await text_sensor.register_text_sensor(var, config)
    
    cg.add(var.set_pins(config[CONF_CS_PIN], config[CONF_DIO0_PIN], config[CONF_RST_PIN]))
    # เพิ่มบรรทัดส่งค่าความถี่ไปที่ C++
    if CONF_FREQUENCY in config:
        cg.add(var.set_frequency(config[CONF_FREQUENCY]))
