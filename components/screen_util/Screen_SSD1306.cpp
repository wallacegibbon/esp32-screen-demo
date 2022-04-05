#include "Screen_SSD1306.h"

#define SSD1306_CONTROL_WRITE_CMD_SINGLE 0x80
#define SSD1306_CONTROL_WRITE_CMD_MULTI 0x00
#define SSD1306_CONTROL_WRITE_DATA_SINGLE 0xC0
#define SSD1306_CONTROL_WRITE_DATA_MULTI 0x40

void Screen_SSD1306::init()
{
    send_init_commands();
    display_on();
}

void Screen_SSD1306::send_init_commands()
{
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
    write_byte(SSD1306_CONTROL_WRITE_CMD_MULTI);

    if (height == 32)
    {
        for (uint8_t cmd : fix_32row_command)
            write_byte(cmd);
    }

    for (uint8_t cmd : init_commands)
        write_byte(cmd);

    stop_transmit();
}

void Screen_SSD1306::set_brightness(uint8_t value)
{
    start_transmit();
    write_byte(SSD1306_CONTROL_WRITE_CMD_MULTI);
    write_byte(0x81);
    write_byte(value);
    stop_transmit();
}

void Screen_SSD1306::up_down_invert()
{
    start_transmit();
    write_byte(SSD1306_CONTROL_WRITE_CMD_MULTI);
    if (direction == 0)
    {
        write_byte(0xA1);
        write_byte(0xC8);
    }
    else
    {
        write_byte(0xA0);
        write_byte(0xC0);
    }
    direction = !direction;
    stop_transmit();
}

void Screen_SSD1306::color_reverse()
{
    start_transmit();
    write_byte(SSD1306_CONTROL_WRITE_CMD_MULTI);
    write_byte(0xA7);
    stop_transmit();
}

void Screen_SSD1306::display_on()
{
    start_transmit();
    write_byte(SSD1306_CONTROL_WRITE_CMD_MULTI);
    // turn on the charge pump
    write_byte(0x8D);
    write_byte(0x14);
    // turn on display
    write_byte(0xAF);
    stop_transmit();
}

void Screen_SSD1306::display_off()
{
    start_transmit();
    write_byte(SSD1306_CONTROL_WRITE_CMD_MULTI);
    // turn off the charge pump
    write_byte(0x8D);
    write_byte(0x10);
    // turn off display
    write_byte(0xAE);
    stop_transmit();
}

void Screen_SSD1306::draw_point(int x, int y, Color_1bit color)
{
    if (x >= width || y >= height)
        return;

    int page_idx = y / 8;
    int byte_idx = y % 8;

    int tmp = buf[x][page_idx];
    tmp &= ~(1 << byte_idx);
    tmp |= color << byte_idx;
    buf[x][page_idx] = tmp;

    start_transmit();

    write_byte(SSD1306_CONTROL_WRITE_CMD_SINGLE);
    write_byte(0xB0 + page_idx);
    write_byte(SSD1306_CONTROL_WRITE_CMD_SINGLE);
    write_byte(((x >> 4) & 0x0F) | 0x10);
    write_byte(SSD1306_CONTROL_WRITE_CMD_SINGLE);
    write_byte(x & 0x0F);

    write_byte(SSD1306_CONTROL_WRITE_DATA_SINGLE);
    write_byte(tmp);

    stop_transmit();
}

void Screen_SSD1306::clear(Color_1bit color)
{
    uint8_t fill_value = color == WHITE_1bit ? 0xFF : 0;

    for (int i = 0; i < 8; i++)
    {
        start_transmit();

        write_byte(SSD1306_CONTROL_WRITE_CMD_SINGLE);
        write_byte(0xB0 + i);
        write_byte(SSD1306_CONTROL_WRITE_DATA_MULTI);
        for (int x = 0; x < width; x++)
            write_byte(fill_value);

        stop_transmit();
    }
}
