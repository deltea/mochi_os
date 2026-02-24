#pragma once

#include <Adafruit_SSD1351.h>

extern Adafruit_SSD1351 display;

// double buffering
extern GFXcanvas16 canvas;
extern GFXcanvas16 lastCanvas;

void initDisplay();
void clearDisplay();
void drawText(const char* text, int16_t x, int16_t y, bool center, const GFXfont* font, uint16_t color);
void updateDisplay();
