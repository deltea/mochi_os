#include <SPI.h>
#include <Adafruit_GFX.h>
#include "constants.h"
#include "assets/icons.h"
#include "assets/fonts/cutepixel.h"
#include "assets/fonts/monogram.h"
#include "ui/screen.h"
#include "ui/player_screen.h"
#include "system/display.h"
#include "system/audio.h"
#include "system/card.h"
#include "core/state.h"

PlayerScreen playerScreen;
Screen* currentScreen = &playerScreen;

uint32_t lastFrameTime = 0;

void drawBoot() {
  canvas.fillScreen(BG);
  display.drawText("mochi_os", SCREEN_WIDTH / 2 + 8, SCREEN_HEIGHT / 2 - 4, true, &cute_pixel8pt7b, FG);
  display.drawText("booting up...", SCREEN_WIDTH / 2, SCREEN_HEIGHT - 10, true, nullptr, FG);
  canvas.drawRGBBitmap(SCREEN_WIDTH / 2 - 36, SCREEN_HEIGHT / 2 - 11, ICON_MUSIC, 16, 9);
  display.update();
}

void setup() {
  Serial.begin(115200);
  while (!Serial) { delay(1); }
  delay(500);

  display.init();
  drawBoot();
  player.init();
  sd.init();
  sd.indexLibrary();

  currentScreen->init(state);
  lastFrameTime = millis();
}

void loop() {
  uint32_t now = millis();
  uint32_t deltaMs = now - lastFrameTime;
  lastFrameTime = now;

  currentScreen->update(state, deltaMs);
  currentScreen->render(state);

  display.update();
  player.feed();
}
