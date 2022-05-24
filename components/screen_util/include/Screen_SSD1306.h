#ifndef __SCREEN_SSD1306_H
#define __SCREEN_SSD1306_H

/// SSD1306 is a 128 x 64 Dot Matrix OLED/PLED Segment/Common Driver with Controller

#include "Common_IIC.h"
#include "Common_SPI.h"
#include "Screen.h"
#include "Screen_Color.h"
#include <cstdint>
#include <functional>

class Screen_SSD1306 : public Screen<Color_1bit> {
public:
    Screen_SSD1306(int width, int height) : Screen(width, height) {}

    void init();
    void display_on();
    void display_off();
    void set_brightness(uint8_t value);
    void up_down_invert();
    void color_reverse();
    void flush();
    void enable_auto_flush() { auto_flush = true; }
    void disable_auto_flush() { auto_flush = false; }
    void draw_point(int x, int y, Color_1bit color) override;
    void clear(Color_1bit color) override;

private:
    void send_init_commands();
    void iterate_screen(std::function<uint8_t(int, int)> fn);

    virtual void write_byte(uint8_t data) {}
    virtual void start_transmit() {}
    virtual void stop_transmit() {}

    virtual void data_single_byte() {}
    virtual void data_multi_bytes() {}
    virtual void cmd_single_byte() {}
    virtual void cmd_multi_bytes() {}

    uint8_t buf[128][8];
    int direction = 0;
    bool auto_flush = false;
};

class Screen_SSD1306_IIC : public Screen_SSD1306 {
    static constexpr uint8_t CTRL_WRITE_CMD_SINGLE = 0x80;
    static constexpr uint8_t CTRL_WRITE_CMD_MULTI = 0x00;
    static constexpr uint8_t CTRL_WRITE_DATA_SINGLE = 0xC0;
    static constexpr uint8_t CTRL_WRITE_DATA_MULTI = 0x40;

public:
    Screen_SSD1306_IIC(int _dev, int addr, int width, int height) : Screen_SSD1306(width, height), dev(_dev, addr) {}

    void init() { Screen_SSD1306::init(); }

private:
    void write_byte(uint8_t data) override { dev.write_byte(data); }
    void start_transmit() override { dev.start_transmit(); }
    void stop_transmit() override { dev.stop_transmit(); }

    void data_single_byte() override { write_byte(CTRL_WRITE_DATA_SINGLE); }
    void data_multi_bytes() override { write_byte(CTRL_WRITE_DATA_MULTI); }
    void cmd_single_byte() override { write_byte(CTRL_WRITE_CMD_SINGLE); }
    void cmd_multi_bytes() override { write_byte(CTRL_WRITE_CMD_MULTI); }

    IIC_Dev dev;
};

#endif
