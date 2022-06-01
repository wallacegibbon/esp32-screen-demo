#include "Screen_16bitColor_SPI.h"
#include <cstdint>

using namespace screen;

void Screen_16bitColor_SPI::init() {
    dev_.init();
    gpio_set_direction(rst_, GPIO_MODE_OUTPUT);
    gpio_set_direction(dc_, GPIO_MODE_OUTPUT);
}

void Screen_16bitColor_SPI::write_data(uint16_t data) {
    dc_high();
    dev_.write_byte(data >> 8);
    dev_.write_byte(data);
}

void Screen_16bitColor_SPI::write_data8(uint8_t data) {
    dc_high();
    dev_.write_byte(data);
}

void Screen_16bitColor_SPI::write_cmd(uint8_t data) {
    dc_low();
    dev_.write_byte(data);
}
