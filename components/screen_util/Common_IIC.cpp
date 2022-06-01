#include "Common_IIC.h"
#include "esp_log.h"
#include <cstdint>

using namespace screen;

void IIC_Dev::start_transmit() {
    cmd_handle_ = i2c_cmd_link_create();
    i2c_master_start(cmd_handle_);
    i2c_master_write_byte(cmd_handle_, addr_ | I2C_MASTER_WRITE, true);
}

void IIC_Dev::stop_transmit() {
    esp_err_t esp_err;

    i2c_master_stop(cmd_handle_);
    esp_err = i2c_master_cmd_begin(dev_, cmd_handle_, 10 / portTICK_PERIOD_MS);
    if (esp_err != ESP_OK) {
        ESP_LOGE("Common_IIC", "configuration failed, error code :%d", esp_err);
    }

    i2c_cmd_link_delete(cmd_handle_);
}
