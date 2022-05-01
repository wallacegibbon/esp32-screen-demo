#include "Screen_SSD1306.h"

void Screen_SSD1306::init() {
    send_init_commands();
    display_on();
}

void Screen_SSD1306::send_init_commands() {
    static const uint8_t init_commands[] = {
            /* normal direction, can be changed by method `up_down_invert` */
            0xA0, 0xC0,

            /* vertical shift, 0 ~ 63 */
            // 0xD3, 20,

            /* Ratio/Oscillator & Clock Divide */
            // 0xD5, 0xF0,

            // 0xD9, 0x22,
    };

    static const uint8_t fix_32row_command[] = {
            /* ... */
            0xA8,
            0x1F,

            /* ... */
            0xDA,
            0x02,
    };

    start_transmit();
    cmd_multi_bytes();

    if (height == 32) {
        for (uint8_t cmd : fix_32row_command) {
            write_byte(cmd);
        }
    }

    for (uint8_t cmd : init_commands) {
        write_byte(cmd);
    }

    stop_transmit();
}

void Screen_SSD1306::set_brightness(uint8_t value) {
    start_transmit();
    cmd_multi_bytes();
    write_byte(0x81);
    write_byte(value);
    stop_transmit();
}

void Screen_SSD1306::up_down_invert() {
    start_transmit();
    cmd_multi_bytes();
    if (direction == 0) {
        write_byte(0xA1);
        write_byte(0xC8);
    } else {
        write_byte(0xA0);
        write_byte(0xC0);
    }
    direction = !direction;
    stop_transmit();
}

void Screen_SSD1306::color_reverse() {
    start_transmit();
    cmd_single_byte();
    write_byte(0xA7);
    stop_transmit();
}

void Screen_SSD1306::display_on() {
    start_transmit();
    cmd_multi_bytes();
    // turn on the charge pump
    write_byte(0x8D);
    write_byte(0x14);
    // turn on display
    write_byte(0xAF);
    stop_transmit();
}

void Screen_SSD1306::display_off() {
    start_transmit();
    cmd_multi_bytes();
    // turn off the charge pump
    write_byte(0x8D);
    write_byte(0x10);
    // turn off display
    write_byte(0xAE);
    stop_transmit();
}

void Screen_SSD1306::draw_point(int x, int y, Color_1bit color) {
    if (x >= width || y >= height) {
        return;
    }

    int page_idx = y / 8;
    int byte_idx = y % 8;

    int tmp = buf[x][page_idx];
    tmp &= ~(1 << byte_idx);
    tmp |= color << byte_idx;
    buf[x][page_idx] = tmp;

    if (!auto_flush) {
        return;
    }

    start_transmit();
    cmd_single_byte();
    write_byte(0xB0 + page_idx);
    cmd_single_byte();
    write_byte(((x >> 4) & 0x0F) | 0x10);
    cmd_single_byte();
    write_byte(x & 0x0F);

    data_single_byte();
    write_byte(tmp);
    stop_transmit();
}

void Screen_SSD1306::iterate_screen(std::function<uint8_t(int, int)> fn) {
    for (int page = 0; page < 8; page++) {
        start_transmit();
        cmd_single_byte();
        write_byte(0xB0 + page);
        cmd_single_byte();
        write_byte(0x00);
        cmd_single_byte();
        write_byte(0x10);

        data_multi_bytes();
        for (int x = 0; x < width; x++) {
            write_byte(fn(x, page));
        }

        stop_transmit();
    }
}

void Screen_SSD1306::flush() {
    iterate_screen([this](int x, int page) { return buf[x][page]; });
}

void Screen_SSD1306::clear(Color_1bit color) {
    uint8_t fill_value = color == WHITE_1bit ? 0xFF : 0;
    iterate_screen([&](int x, int page) { return fill_value; });
}
