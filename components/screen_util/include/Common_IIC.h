#ifndef __COMMON_IIC_H
#define __COMMON_IIC_H

#include "driver/i2c.h"
#include <cstdint>
#include <stdio.h>

namespace screen {

class IIC_Dev {
  i2c_cmd_handle_t cmd_handle_;
  int dev_;
  int addr_;

public:
  IIC_Dev(int dev, int addr) : dev_(dev), addr_(addr << 1) {}

  void start_transmit();
  void stop_transmit();
  void write_byte(uint8_t data) { i2c_master_write_byte(cmd_handle_, data, true); }
};

} // namespace screen

#endif
