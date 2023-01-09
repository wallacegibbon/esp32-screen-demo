#include "Screen_ST7735.h"
#include "freertos/task.h"

using namespace screen;

void Screen_ST7735::send_init_commands() {
  /// turn off sleep mode
  write_cmd(0x11);
  vTaskDelay(100 / portTICK_PERIOD_MS);

  /// display inversion mode (0 is black, -1 is white)
  write_cmd(0x21);

  /// Set the frame frequency of the full colors normal mode
  write_cmd(0xB1);
  /// Frame rate=fosc/((RTNA x 2 + 40) x (LINE + FPA + BPA +2))
  /// fosc = 850kHz
  write_data8(0x05); // RTNA
  write_data8(0x3A); // FPA
  write_data8(0x3A); // BPA

  /// Set the frame frequency of the Idle mode
  write_cmd(0xB2);
  /// Frame rate=fosc/((RTNB x 2 + 40) x (LINE + FPB + BPB +2))
  /// fosc = 850kHz
  write_data8(0x05); // RTNB
  write_data8(0x3A); // FPB
  write_data8(0x3A); // BPB

  /// Set the frame frequency of the Partial mode/ full colors
  write_cmd(0xB3);
  write_data8(0x05);
  write_data8(0x3A);
  write_data8(0x3A);
  write_data8(0x05);
  write_data8(0x3A);
  write_data8(0x3A);

  write_cmd(0xB4);
  write_data8(0x03);

  write_cmd(0xC0);
  write_data8(0x62);
  write_data8(0x02);
  write_data8(0x04);

  write_cmd(0xC1);
  write_data8(0xC0);

  write_cmd(0xC2);
  write_data8(0x0D);
  write_data8(0x00);

  write_cmd(0xC3);
  write_data8(0x8D);
  write_data8(0x6A);

  write_cmd(0xC4);
  write_data8(0x8D);
  write_data8(0xEE);

  write_cmd(0xC5);
  write_data8(0x0E); /// VCOM

  write_cmd(0xE0);
  write_data8(0x10);
  write_data8(0x0E);
  write_data8(0x02);
  write_data8(0x03);
  write_data8(0x0E);
  write_data8(0x07);
  write_data8(0x02);
  write_data8(0x07);
  write_data8(0x0A);
  write_data8(0x12);
  write_data8(0x27);
  write_data8(0x37);
  write_data8(0x00);
  write_data8(0x0D);
  write_data8(0x0E);
  write_data8(0x10);

  write_cmd(0xE1);
  write_data8(0x10);
  write_data8(0x0E);
  write_data8(0x03);
  write_data8(0x03);
  write_data8(0x0F);
  write_data8(0x06);
  write_data8(0x02);
  write_data8(0x08);
  write_data8(0x0A);
  write_data8(0x13);
  write_data8(0x26);
  write_data8(0x36);
  write_data8(0x00);
  write_data8(0x0D);
  write_data8(0x0E);
  write_data8(0x10);

  /// 16 bit color
  write_cmd(0x3A);
  write_data8(0x05);

  write_cmd(0x36);
  write_data8(0x78);

  /// Display On
  write_cmd(0x29);
}

void Screen_ST7735::addr_set(const Point &p1, const Point &p2) {
  /// column address settings
  write_cmd(0x2A);
  write_data(p1.x + 1);
  write_data(p2.x + 1);

  /// row address setting
  write_cmd(0x2B);
  write_data(p1.y + 26);
  write_data(p2.y + 26);

  /// memory write
  write_cmd(0x2C);
}

void Screen_ST7735::draw_point(const Point &p, Color_16bit color) {
  if (p.x > size_.x || p.y > size_.y) { return; }
  addr_set(p, p);
  write_data(static_cast<uint16_t>(color));
}

void Screen_ST7735::fill(const Point &p1, const Point &p2, Color_16bit color) {
  addr_set(p1, p2);
  for (int i = p1.y; i <= p2.y; i++) {
    for (int j = p1.x; j <= p2.x; j++) {
      write_data(static_cast<uint16_t>(color));
    }
  }
}

void Screen_ST7735_SPI::init() {
  gpio_set_direction(rst_, GPIO_MODE_OUTPUT);
  gpio_set_direction(dc_, GPIO_MODE_OUTPUT);

  rst_low();
  vTaskDelay(200 / portTICK_PERIOD_MS);

  rst_high();
  vTaskDelay(20 / portTICK_PERIOD_MS);

  send_init_commands();
}

void Screen_ST7735_SPI::write_data(uint16_t data) {
  dc_high();
  dev_.write_byte(data >> 8);
  dev_.write_byte(data);
}

void Screen_ST7735_SPI::write_data8(uint8_t data) {
  dc_high();
  dev_.write_byte(data);
}

void Screen_ST7735_SPI::write_cmd(uint8_t data) {
  dc_low();
  dev_.write_byte(data);
}
