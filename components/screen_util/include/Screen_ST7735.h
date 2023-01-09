#ifndef __SCREEN_ST7735_H
#define __SCREEN_ST7735_H

/// ST7735 is a 132RGB x 162dot 262K Color with Frame Memory Single-Chip TFT Controller/Driver

#include "Common_SPI.h"
#include "Screen.h"
#include "Screen_Color.h"
#include "driver/gpio.h"
#include "driver/spi_master.h"
#include <cstdint>

namespace screen {

class Screen_ST7735 : public Screen<Color_16bit> {
public:
  Screen_ST7735(int width, int height) : Screen(width, height) {}

  void draw_point(const Point &p, Color_16bit color) override;
  void fill(const Point &p1, const Point &p2, Color_16bit color) override;

  virtual void write_data(uint16_t data) {}
  virtual void write_data8(uint8_t data) {}
  virtual void write_cmd(uint8_t data) {}

protected:
  void send_init_commands();

private:
  void addr_set(const Point &p1, const Point &p2);
};

class Screen_ST7735_SPI : public Screen_ST7735 {
  SPI_Dev dev_;
  gpio_num_t rst_;
  gpio_num_t dc_;

public:
  Screen_ST7735_SPI(
    int dev, spi_device_handle_t *slave_dev, gpio_num_t rst, gpio_num_t dc, int width, int height
  )
    : Screen_ST7735(width, height), dev_(dev, *slave_dev), rst_(rst), dc_(dc) {}

  void init();

protected:
  void write_data(uint16_t data) override;
  void write_data8(uint8_t data) override;
  void write_cmd(uint8_t data) override;

private:
  void rst_high() { gpio_set_level(rst_, 1); }
  void rst_low() { gpio_set_level(rst_, 0); }
  void dc_high() { gpio_set_level(dc_, 1); }
  void dc_low() { gpio_set_level(dc_, 0); }
};

} // namespace screen

#endif
