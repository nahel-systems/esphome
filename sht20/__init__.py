import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import i2c, sensor
from esphome.const import CONF_ID, CONF_TEMPERATURE, CONF_HUMIDITY, UNIT_CELSIUS, UNIT_PERCENT, ICON_THERMOMETER

sht20_ns = cg.esphome_ns.namespace('sht20')
SHT20Component = sht20_ns.class_('SHT20Component', cg.PollingComponent, i2c.I2CDevice)

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(SHT20Component),
    cv.Required(CONF_TEMPERATURE): sensor.sensor_schema(
        unit_of_measurement=UNIT_CELSIUS,
        icon=ICON_THERMOMETER,
        accuracy_decimals=1,
    ),
    cv.Required(CONF_HUMIDITY): sensor.sensor_schema(
        unit_of_measurement=UNIT_PERCENT,
        icon='mdi:water-percent',
        accuracy_decimals=1,
    ),
}).extend(cv.polling_component_schema('60s')).extend(i2c.i2c_device_schema(0x40))

def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    yield cg.register_component(var, config)
    yield i2c.register_i2c_device(var, config)
    temp = yield sensor.new_sensor(config[CONF_TEMPERATURE])
    hum = yield sensor.new_sensor(config[CONF_HUMIDITY])
    cg.add(var.set_temperature_sensor(temp))
    cg.add(var.set_humidity_sensor(hum))
