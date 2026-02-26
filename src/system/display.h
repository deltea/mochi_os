#pragma once

#include <Adafruit_SSD1351.h>

extern Adafruit_SSD1351 d;

// double buffering
extern GFXcanvas16 canvas;
extern GFXcanvas16 lastCanvas;

struct Display {
public:
  void init();
  void clear();
  void drawText(std::string, int16_t x, int16_t y, bool center, const GFXfont* font, uint16_t color);
  void update();
};

extern Display display;
