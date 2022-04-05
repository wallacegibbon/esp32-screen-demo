#ifndef __SCREEN_SSD1306_H
#define __SCREEN_SSD1306_H

/**
 * SSD1306 is a 128 x 64 Dot Matrix OLED/PLED Segment/Common Driver with Controller
 */

#include <stdint.h>
#include "Screen.h"
#include "Screen_Color.h"
#include "Common_SPI.h"
#include "Common_IIC.h"

class Screen_SSD1306 : public Screen<Color_1bit>
{
public:
    Screen_SSD1306(int width, int height) : Screen(width, height) {}

    void init();
    void display_on();
    void display_off();
    void set_brightness(uint8_t value);
    void up_down_invert();
    void color_reverse();
    void draw_point(int x, int y, Color_1bit color) override;
    void clear(Color_1bit color) override;

private:
    void send_init_commands();

    virtual void start_transmit() {}
    virtual void stop_transmit() {}
    virtual void write_byte(uint8_t data) {}

    uint8_t buf[128][8];
    int direction = 0;
};

class Screen_SSD1306_IIC : public Screen_SSD1306
{
public:
    Screen_SSD1306_IIC(int _dev, int addr, int width, int height)
        : Screen_SSD1306(width, height), dev(_dev, addr) {}

    void init() { Screen_SSD1306::init(); }

private:
    void start_transmit() override { dev.start_transmit(); }
    void stop_transmit() override { dev.stop_transmit(); }
    void write_byte(uint8_t data) override { dev.write_byte(data); }

    IIC_Dev dev;
};

#endif
