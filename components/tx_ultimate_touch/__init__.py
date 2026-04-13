import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import uart

DEPENDENCIES = ["uart"]

tx_ns = cg.esphome_ns.namespace("tx_ultimate_touch")
TxUltimateTouch = tx_ns.class_("TxUltimateTouch", cg.Component, uart.UARTDevice)

CONFIG_SCHEMA = cv.Schema({}).extend(uart.UART_DEVICE_SCHEMA)

async def to_code(config):
    var = cg.new_Pvariable(config["id"])
    await cg.register_component(var, config)
    await uart.register_uart_device(var, config)
