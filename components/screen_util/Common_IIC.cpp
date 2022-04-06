#include <cstdint>
#include "Common_IIC.h"
#include "esp_log.h"

void IIC_Dev::start_transmit()
{
    cmd_handle = i2c_cmd_link_create();
    i2c_master_start(cmd_handle);
    i2c_master_write_byte(cmd_handle, addr | I2C_MASTER_WRITE, true);
}

void IIC_Dev::stop_transmit()
{
    esp_err_t esp_err;

    i2c_master_stop(cmd_handle);
    esp_err = i2c_master_cmd_begin(dev, cmd_handle, 10 / portTICK_PERIOD_MS);
    if (esp_err != ESP_OK)
    {
        ESP_LOGE("Common_IIC", "configuration failed, error code :%d", esp_err);
    }

    i2c_cmd_link_delete(cmd_handle);
}
