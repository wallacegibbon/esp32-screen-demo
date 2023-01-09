idf_component_register(
  REQUIRES driver
  SRCS
  "Common_IIC.cpp"
  "Common_SPI.cpp"
  "Screen_SSD1306.cpp"
  "Screen_ST7735.cpp"
  INCLUDE_DIRS
  "include"
)
