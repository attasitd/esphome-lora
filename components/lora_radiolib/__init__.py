import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.const import CONF_ID, CONF_FREQUENCY

# บังคับว่าต้องมีตั้งค่า spi: ใน YAML ด้วย
DEPENDENCIES = ['spi']

lora_ns = cg.esphome_ns.namespace('lora_radiolib')
LoRaRadioLib = lora_ns.class_('LoRaRadioLib', cg.Component)

CONF_CS_PIN = 'cs_pin'
CONF_DIO0_PIN = 'dio0_pin'
CONF_RST_PIN = 'rst_pin'

# โครงสร้างคำสั่งที่ผู้ใช้ต้องพิมพ์ใน YAML
CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(LoRaRadioLib),
    cv.Required(CONF_CS_PIN): cv.int_,
    cv.Required(CONF_DIO0_PIN): cv.int_,
    cv.Required(CONF_RST_PIN): cv.int_,
    cv.Optional(CONF_FREQUENCY, default=433.0): cv.float_,
}).extend(cv.COMPONENT_SCHEMA)

def to_code(config):
    # ไฮไลท์: สั่งให้โหลด RadioLib v6.3.0 อัตโนมัติ ผู้ใช้ไม่ต้องพิมพ์เอง!
    cg.add_library("jgromes/RadioLib", "6.3.0")
    
    var = cg.new_Pvariable(config[CONF_ID])
    yield cg.register_component(var, config)
    
    # ส่งค่า Pin และความถี่ไปให้ไฟล์ C++
    cg.add(var.set_pins(config[CONF_CS_PIN], config[CONF_DIO0_PIN], config[CONF_RST_PIN]))
    cg.add(var.set_frequency(config[CONF_FREQUENCY]))
