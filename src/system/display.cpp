#include "display.h"
#include <constants.h>
#include "assets/fonts/monogram.h"

Adafruit_SSD1351 display(SCREEN_WIDTH, SCREEN_HEIGHT, &SPI, OLED_CS, OLED_DC, OLED_RST);
GFXcanvas16 canvas(SCREEN_WIDTH, SCREEN_HEIGHT);
GFXcanvas16 lastCanvas(SCREEN_WIDTH, SCREEN_HEIGHT);

void initDisplay() {
  display.begin();
  // display.setSPISpeed(8000000);
  display.fillScreen(BG);
  display.setTextColor(FG);
}

void clearDisplay() {
  display.fillScreen(BG);
}

void updateDisplay() {
  uint16_t* curr = canvas.getBuffer();
  uint16_t* prev = lastCanvas.getBuffer();

  for (int y = 0; y < SCREEN_HEIGHT; y++) {
    for (int x = 0; x < SCREEN_WIDTH; x++) {
      int index = y * SCREEN_WIDTH + x;
      if (curr[index] != prev[index]) {
        display.drawPixel(x, y, curr[index]);
        prev[index] = curr[index];
      }
    }
  }
}

void drawText(const char* text, int16_t x, int16_t y, bool center = false, const GFXfont* font = nullptr, uint16_t color = FG) {
  if (font != nullptr) {
    canvas.setFont(font);
  } else {
    // monogram font is default
    canvas.setFont(&monogram8pt7b);
  }

  canvas.setTextColor(color);

  int16_t x1, y1;
  uint16_t w, h;

  if (center) {
    canvas.getTextBounds(text, 0, 0, &x1, &y1, &w, &h);
    // center horizontally
    x = x - (w / 2);
  }

  canvas.setCursor(x, y);
  canvas.print(text);
}
