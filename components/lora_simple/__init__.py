import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import text_sensor
from esphome.const import CONF_ID, CONF_FREQUENCY

# เพิ่มชื่อเรียกค่าตัวแปรใหม่
CONF_TX_POWER = "tx_power"
CONF_SPREADING_FACTOR = "spreading_factor"
CONF_CODING_RATE = "coding_rate"
CONF_CS_PIN = 'cs_pin'
CONF_DIO0_PIN = 'dio0_pin'
CONF_RST_PIN = 'rst_pin'

lora_ns = cg.esphome_ns.namespace('lora_simple')
LoRaComponent = lora_ns.class_('LoRaComponent', text_sensor.TextSensor, cg.Component)

CONFIG_SCHEMA = text_sensor.text_sensor_schema(LoRaComponent).extend({
    cv.Required(CONF_CS_PIN): cv.int_,
    cv.Required(CONF_DIO0_PIN): cv.int_,
    cv.Required(CONF_RST_PIN): cv.int_,
    cv.Optional(CONF_FREQUENCY, default=433.0): cv.float_,
    # เพิ่มส่วนตั้งค่าใหม่พร้อมค่า Default
    cv.Optional(CONF_TX_POWER, default=17): cv.int_range(min=2, max=20),
    cv.Optional(CONF_SPREADING_FACTOR, default=7): cv.int_range(min=6, max=12),
    cv.Optional(CONF_CODING_RATE, default=5): cv.int_range(min=5, max=8),
}).extend(cv.COMPONENT_SCHEMA)

async def to_code(config):
    cg.add_library("sandeepmistry/LoRa", "0.8.0")
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await text_sensor.register_text_sensor(var, config)
    
    cg.add(var.set_pins(config[CONF_CS_PIN], config[CONF_DIO0_PIN], config[CONF_RST_PIN]))
    cg.add(var.set_frequency(config[CONF_FREQUENCY]))
    # ส่งค่าใหม่ไปที่ C++
    cg.add(var.set_tx_power(config[CONF_TX_POWER]))
    cg.add(var.set_spreading_factor(config[CONF_SPREADING_FACTOR]))
    cg.add(var.set_coding_rate(config[CONF_CODING_RATE]))
