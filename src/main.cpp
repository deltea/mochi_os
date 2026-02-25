#include <SPI.h>

#include "assets/icons.h"
#include "ui/screen.h"
#include "ui/player_screen.h"
#include "constants.h"
#include "system/display.h"
#include "system/audio.h"
#include "assets/fonts/cutepixel.h"
#include "assets/fonts/monogram.h"
#include "system/sd.h"
#include "system/playback.h"
#include "state.h"

PlayerScreen playerScreen;
Screen* currentScreen = &playerScreen;

uint32_t lastFrameTime = 0;

void drawBoot() {
  canvas.fillScreen(BG);
  drawText("mochi_os", SCREEN_WIDTH / 2 + 8, SCREEN_HEIGHT / 2 - 4, true, &cute_pixel8pt7b, FG);
  drawText("booting up...", SCREEN_WIDTH / 2, SCREEN_HEIGHT - 10, true, nullptr, FG);
  canvas.drawRGBBitmap(SCREEN_WIDTH / 2 - 36, SCREEN_HEIGHT / 2 - 11, ICON_MUSIC, 16, 9);
  updateDisplay();
}

void setup() {
  Serial.begin(115200);
  while (!Serial) { delay(1); }
  delay(500);

  initDisplay();
  drawBoot();
  initAudio();
  initSD();
  indexLibrary();

  // Track americanIdiot = {
  //   "American Idiot",
  //   "Green Day",
  //   "/tracks/American Idiot/cover.raw",
  //   "/tracks/American Idiot/audio.mp3"
  // };
  // Track capableOfLove = {
  //   "Capable of Love",
  //   "PinkPantheress",
  //   "/tracks/Capable of Love/cover.raw",
  //   "/tracks/Capable of Love/audio.mp3"
  // };

  // playTrack(americanIdiot);

  currentScreen->init(state);
  lastFrameTime = millis();
}

void loop() {
  uint32_t now = millis();
  uint32_t deltaMs = now - lastFrameTime;
  lastFrameTime = now;

  currentScreen->update(state, deltaMs);
  currentScreen->render(state);

  updateDisplay();
  feedPlayer();
}
