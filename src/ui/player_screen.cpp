#include "player_screen.h"
#include "constants.h"
#include "system/display.h"
#include "SD.h"
#include "core/playback.h"
#include "system/sd.h"

void PlayerScreen::init(State &state) {
  state.addPlaylistToQueue(state.playlists[5]);
  // play();
  playTrack(getTrackFromPath(state.queue[state.currentTrackIndex].c_str()));
  drawCover(getTrackFromPath(state.queue[state.currentTrackIndex].c_str()).cover_path.c_str());
}

void PlayerScreen::update(State &state, uint32_t deltaMs) {
  // serial input handling for player controls
  if (Serial.available()) {
    char command = Serial.read();
    if (command == 'n') {
      nextTrack();
    } else if (command == 'p') {
      previousTrack();
    }
  }
}

void PlayerScreen::render(State &state) {
  // canvas.fillScreen(BG);
}

void PlayerScreen::drawCover(std::string path) {
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
