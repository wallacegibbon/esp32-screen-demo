#ifndef __SCREEN_ST7735_H
#define __SCREEN_ST7735_H

/// ST7735 is a 132RGB x 162dot 262K Color with Frame Memory Single-Chip TFT Controller/Driver

#include "Screen_16bitColor_SPI.h"

namespace screen {

class Screen_ST7735 : public Screen_16bitColor_SPI {
public:
	Screen_ST7735(
		int dev, gpio_num_t rst, gpio_num_t dc, int width, int height
	) : Screen_16bitColor_SPI(dev, rst, dc, width, height) {}

	void draw_point(const Point &p, Color_16bit color) override;
	void fill(const Point &p1, const Point &p2, Color_16bit color) override;

	void init();

private:
	void send_init_commands();
	void addr_set(const Point &p1, const Point &p2);
};

} // namespace screen

#endif
