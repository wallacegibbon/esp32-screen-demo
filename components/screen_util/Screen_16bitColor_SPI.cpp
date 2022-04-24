#include "Screen_16bitColor_SPI.h"
#include <cstdint>

void Screen_16bitColor_SPI::init()
{
    dev.init();
    gpio_set_direction(rst, GPIO_MODE_OUTPUT);
    gpio_set_direction(dc, GPIO_MODE_OUTPUT);
}

void Screen_16bitColor_SPI::write_data(uint16_t data)
{
    dc_high();
    dev.write_byte(data >> 8);
    dev.write_byte(data);
}

void Screen_16bitColor_SPI::write_data8(uint8_t data)
{
    dc_high();
    dev.write_byte(data);
}

void Screen_16bitColor_SPI::write_cmd(uint8_t data)
{
    dc_low();
    dev.write_byte(data);
}
