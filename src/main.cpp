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

State state;

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

void drawCover(std::string path) {
  File cover = SD.open(path.c_str());
  if (!cover) {
    Serial.println("couldn't open cover file");
    return;
  }

  if (cover.available()) {
    uint16_t* coverBuffer = (uint16_t*)malloc(86 * 86 * sizeof(uint16_t));
    cover.read((uint8_t*)coverBuffer, 86 * 86 * sizeof(uint16_t));
    canvas.drawRGBBitmap(SCREEN_WIDTH / 2 - 43, SCREEN_HEIGHT / 3 - 38, coverBuffer, 86, 86);
  }
  cover.close();
}

void playTrack(Track track) {
  playFile(track.audio_path.c_str());
  drawCover(track.cover_path);
}

void setup() {
  Serial.begin(115200);
  while (!Serial) { delay(1); }
  delay(500);

  initDisplay();
  drawBoot();
  initAudio();
  initSD();
  listPlaylists();

  Track americanIdiot = {
    "American Idiot",
    "Green Day",
    "/tracks/American Idiot/cover.raw",
    "/tracks/American Idiot/audio.mp3"
  };

  playTrack(americanIdiot);

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
