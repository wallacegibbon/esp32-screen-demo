#include "Screen_SSD1306.h"
#include "driver/i2c.h"
#include "esp_log.h"
#include "freertos/task.h"
#include <iostream>

void i2c_device_init() {
  i2c_config_t config;
  config.mode = I2C_MODE_MASTER;
  config.sda_io_num = GPIO_NUM_22;
  config.scl_io_num = GPIO_NUM_23;
  config.sda_pullup_en = GPIO_PULLUP_ENABLE;
  config.scl_pullup_en = GPIO_PULLUP_ENABLE;
  config.master.clk_speed = 400000;
  config.clk_flags = 0;

  i2c_param_config(I2C_NUM_0, &config);
  i2c_driver_install(I2C_NUM_0, I2C_MODE_MASTER, 0, 0, 0);
}

screen::Screen_SSD1306_IIC scr1(I2C_NUM_0, 0x3C, 128, 64);

static void fancy_display_1() {
  static unsigned short current_color = 0;
  static bool color = false;
  for (int i = 0; i < 31; i++) {
    current_color += 20;
    scr1.draw_circle(screen::Point(64, 32), i, static_cast<screen::Color_1bit>(color));

    color = !color;
    scr1.flush();
  }
  vTaskDelay(10 / portTICK_PERIOD_MS);
}

static void fancy_display_2() {
  static int cur = 0;
  static int inc = 1;
  for (int i = 0; i < 31; i++) {
    screen::Color_1bit color = cur == i ? screen::Color_1bit::BLACK : screen::Color_1bit::WHITE;
    scr1.draw_circle(screen::Point(64, 32), i, color);
  }
  scr1.flush();

  if (cur == 31)
    inc = -1;
  else if (cur == 0)
    inc = 1;

  cur += inc;
  // vTaskDelay(10 / portTICK_PERIOD_MS);
}

void entry() {
  std::cout << "hello, this message is from the entry." << std::endl;
  std::cout << "another line." << std::endl;

  i2c_device_init();

  scr1.init();
  // scr1.up_down_invert();
  // scr1.clear(Color_1bit::BLACK);

  scr1.draw_rectangle(screen::Point(64 - 50, 32 - 20), screen::Point(64 + 50, 32 + 20),
                      screen::Color_1bit::WHITE);

  scr1.draw_circle(screen::Point(64 - 50, 32 - 20), 5, screen::Color_1bit::WHITE);

  scr1.flush();
  // scr1.enable_auto_flush();

  while (1)
    fancy_display_2();
}

extern "C" {

void app_main(void) { entry(); }
}
