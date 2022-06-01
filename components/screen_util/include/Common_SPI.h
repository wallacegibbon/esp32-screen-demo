#ifndef __COMMON_SPI_H
#define __COMMON_SPI_H

#include "driver/spi_master.h"
#include <cstdint>

namespace screen {

class SPI_Dev {
public:
    SPI_Dev(int dev) : dev_(dev) {}

    void init() {}
    void write_byte(uint8_t data) {}

private:
    int dev_;
};

} // namespace screen

#endif
