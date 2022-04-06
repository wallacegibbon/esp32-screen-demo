#include <iostream>
#include <cstring>
#include "driver/i2c.h"
#include "esp_log.h"
#include "Screen_SSD1306.h"

void i2c_device_init()
{
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

Screen_SSD1306_IIC scr1(I2C_NUM_0, 0x3C, 128, 64);

static void update_loop_display()
{
    static unsigned short current_color = 0;
    static bool color = false;
    for (int i = 0; i < 31; i++)
    {
        current_color += 20;
        scr1.draw_circle(64, 32, i, static_cast<Color_1bit>(color));
        color = !color;
        scr1.flush();
    }
    vTaskDelay(10 / portTICK_PERIOD_MS);
}

void entry()
{
    std::cout << "hello, this message is from the entry." << std::endl;
    std::cout << "another line." << std::endl;

    i2c_device_init();

    scr1.init();
    // scr1.up_down_invert();
    scr1.clear(BLACK_1bit);
    scr1.draw_rectangle(64 - 50, 32 - 20, 64 + 50, 32 + 20, WHITE_1bit);
    scr1.draw_circle(64 - 50, 32 - 20, 5, WHITE_1bit);
    scr1.flush();
    // scr1.enable_auto_flush();
    while (1)
        update_loop_display();
}

extern "C"
{
    void app_main(void)
    {
        entry();
    }
}