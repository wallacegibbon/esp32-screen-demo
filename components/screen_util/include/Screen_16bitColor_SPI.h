#ifndef __SCREEN_16BITCOLOR_SPI_H
#define __SCREEN_16BITCOLOR_SPI_H

#include "Common_SPI.h"
#include "Screen.h"
#include "Screen_Color.h"
#include "driver/gpio.h"
#include "driver/spi_master.h"
#include <cstdint>

class Screen_16bitColor_SPI : public Screen<Color_16bit> {
public:
    Screen_16bitColor_SPI(int _dev, gpio_num_t _rst, gpio_num_t _dc, int width, int height)
            : Screen(width, height), dev(_dev), rst(_rst), dc(_dc) {}

    void init();

protected:
    void write_data(uint16_t data);
    void write_data8(uint8_t data);
    void write_cmd(uint8_t data);

    void rst_high() { gpio_set_level(rst, 1); }
    void rst_low() { gpio_set_level(rst, 0); }

private:
    void dc_high() { gpio_set_level(dc, 1); }
    void dc_low() { gpio_set_level(dc, 0); }

    SPI_Dev dev;
    gpio_num_t rst;
    gpio_num_t dc;
};

#endif
