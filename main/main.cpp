#include "Screen_SSD1306.h"
#include "driver/i2c.h"
#include "driver/spi_master.h"
#include "esp_log.h"
#include "freertos/task.h"
#include <iostream>

screen::Screen_SSD1306_IIC scr1(I2C_NUM_0, 0x3C, 128, 64);

void i2c_device_init() {
  esp_err_t ret;
  i2c_config_t config;

  config.mode = I2C_MODE_MASTER;
  config.sda_io_num = GPIO_NUM_41;
  config.scl_io_num = GPIO_NUM_40;
  config.sda_pullup_en = GPIO_PULLUP_ENABLE;
  config.scl_pullup_en = GPIO_PULLUP_ENABLE;
  config.master.clk_speed = 400000;
  config.clk_flags = 0;

  ret = i2c_param_config(I2C_NUM_0, &config);
  ESP_ERROR_CHECK(ret);

  ret = i2c_driver_install(I2C_NUM_0, I2C_MODE_MASTER, 0, 0, 0);
  ESP_ERROR_CHECK(ret);
}

void spi_device_init(spi_device_handle_t *dev) {
  esp_err_t ret;
  spi_bus_config_t bus_config;

  bus_config.mosi_io_num = GPIO_NUM_3;
  bus_config.miso_io_num = GPIO_NUM_3;
  bus_config.sclk_io_num = GPIO_NUM_5;
  bus_config.quadwp_io_num = -1;
  bus_config.quadhd_io_num = -1;
  bus_config.max_transfer_sz = 160 * 80 * 2 + 8;
  bus_config.flags = 0;
  bus_config.intr_flags = 0;
  ret = spi_bus_initialize(SPI2_HOST, &bus_config, SPI_DMA_DISABLED);
  ESP_ERROR_CHECK(ret);

  spi_device_interface_config_t interface_config;
  interface_config.address_bits = 0;
  interface_config.command_bits = 0;
  interface_config.mode = 0;
  interface_config.duty_cycle_pos = 0;
  interface_config.cs_ena_pretrans = 0;
  interface_config.cs_ena_posttrans = 0;
  interface_config.input_delay_ns = 0;
  interface_config.clock_speed_hz = 0;
  interface_config.spics_io_num = GPIO_NUM_4;
  interface_config.flags = SPI_DEVICE_NO_DUMMY;
  interface_config.queue_size = 1;
  interface_config.pre_cb = 0;
  interface_config.post_cb = 0;

  ret = spi_bus_add_device(SPI2_HOST, &interface_config, dev);
  ESP_ERROR_CHECK(ret);
}

static void fancy_display_1() {
  static unsigned short current_color = 0;
  static bool color = false;
  for (int i = 0; i < 31; i++) {
    current_color += 20;
    scr1.draw_circle(screen::Point{64, 32}, i, static_cast<screen::Color_1bit>(color));

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
    scr1.draw_circle(screen::Point{64, 32}, i, color);
  }
  scr1.flush();

  if (cur == 31) {
    inc = -1;
  } else if (cur == 0) {
    inc = 1;
  }

  cur += inc;
  // vTaskDelay(10 / portTICK_PERIOD_MS);
}

void entry() {
  std::cout << "hello, this message is from the entry." << std::endl;
  std::cout << "another line." << std::endl;

  i2c_device_init();

  scr1.init();
  // scr1.up_down_invert();
  scr1.clear(screen::Color_1bit::BLACK);

  scr1.draw_rectangle(
    screen::Point{64 - 50, 32 - 20}, screen::Point{64 + 50, 32 + 20}, screen::Color_1bit::WHITE
  );

  // scr1.draw_line(screen::Point{10, 50}, screen::Point{10, 10}, screen::Color_1bit::WHITE);

  scr1.draw_circle(screen::Point{64 - 50, 32 - 20}, 5, screen::Color_1bit::WHITE);

  scr1.flush();
  // scr1.enable_auto_flush();

  while (1) {
    fancy_display_2();
  }
}

extern "C" {

void app_main(void) { entry(); }
}
