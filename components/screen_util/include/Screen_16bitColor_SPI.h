#ifndef __SCREEN_16BITCOLOR_SPI_H
#define __SCREEN_16BITCOLOR_SPI_H

#include "Common_SPI.h"
#include "Screen.h"
#include "Screen_Color.h"
#include "driver/gpio.h"
#include "driver/spi_master.h"
#include <cstdint>

namespace screen {

class Screen_16bitColor_SPI : public Screen<Color_16bit> {
public:
    Screen_16bitColor_SPI(int dev, gpio_num_t rst, gpio_num_t dc, int width, int height)
            : Screen(width, height), dev_(dev), rst_(rst), dc_(dc) {}

    void init();

protected:
    void write_data(uint16_t data);
    void write_data8(uint8_t data);
    void write_cmd(uint8_t data);

    void rst_high() { gpio_set_level(rst_, 1); }
    void rst_low() { gpio_set_level(rst_, 0); }

private:
    void dc_high() { gpio_set_level(dc_, 1); }
    void dc_low() { gpio_set_level(dc_, 0); }

private:
    SPI_Dev dev_;
    gpio_num_t rst_;
    gpio_num_t dc_;
};

} // namespace screen

#endif
