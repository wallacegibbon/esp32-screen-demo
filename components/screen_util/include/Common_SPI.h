#ifndef __COMMON_SPI_H
#define __COMMON_SPI_H

#include "driver/spi_master.h"
#include <cstdint>

namespace screen {

class SPI_Dev {
  spi_device_handle_t slave_dev_;
  int dev_;

public:
  SPI_Dev(int dev, spi_device_handle_t &slave_dev) : slave_dev_(slave_dev), dev_(dev) {}

  void write_byte(uint8_t data) {}
};

} // namespace screen

#endif
