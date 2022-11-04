#ifndef __SCREEN_COLOR_H
#define __SCREEN_COLOR_H

#include <cstdint>

namespace screen {

/// For 16 bit color, Red:Green:Blue == 5:6:5
enum class Color_16bit : uint16_t {
  WHITE = 0xFFFF,
  BLACK = 0x0000,
  BLUE = 0x001F,
  BRED = 0XF81F,
  GRED = 0XFFE0,
  GBLUE = 0X07FF,
  RED = 0xF800,
  MAGENTA = 0xF81F,
  GREEN = 0x07E0,
  CYAN = 0x7FFF,
  YELLOW = 0xFFE0,
  BROWN = 0XBC40,
  BRRED = 0XFC07, /// maroon
  GRAY = 0X8430,

  DARKBLUE = 0X01CF,
  LIGHTBLUE = 0X7D7C,
  GRAYBLUE = 0X5458,

  LIGHTGREEN = 0X841F,
  LGRAY = 0XC618,
  LGRAYBLUE = 0XA651,
  LBBLUE = 0X2B12,
};

enum class Color_1bit : uint8_t {
  WHITE = 1,
  BLACK = 0,
};

} // namespace screen

#endif
