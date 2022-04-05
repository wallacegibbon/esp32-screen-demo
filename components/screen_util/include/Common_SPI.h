#ifndef __COMMON_SPI_H
#define __COMMON_SPI_H

#include <stdint.h>
#include "driver/spi_master.h"

class SPI_Dev
{
public:
    SPI_Dev(int _dev) : dev(_dev) {}

    void init() {}
    void write_byte(uint8_t data) {}

private:
    int dev;
};

#endif
