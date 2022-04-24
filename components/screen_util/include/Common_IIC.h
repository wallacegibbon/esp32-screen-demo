#ifndef __COMMON_IIC_H
#define __COMMON_IIC_H

#include "driver/i2c.h"
#include <cstdint>
#include <stdio.h>

class IIC_Dev
{
public:
    IIC_Dev(int _dev, int _addr) : dev(_dev), addr(_addr << 1) {}

    void start_transmit();
    void stop_transmit();
    void write_byte(uint8_t data) { i2c_master_write_byte(cmd_handle, data, true); }

private:
    int dev;
    int addr;
    i2c_cmd_handle_t cmd_handle;
};

#endif
