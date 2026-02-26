#include "player_screen.h"
#include "constants.h"
#include "system/display.h"
#include "system/card.h"
#include "system/audio.h"

void PlayerScreen::init(State &state) {
  state.addPlaylistToQueue(state.playlists[4]);
  player.playTrack(state.library[state.queue[state.currentTrackIndex]]);
  drawCover(state.library[state.queue[state.currentTrackIndex]].cover_path);
}

void PlayerScreen::update(State &state, uint32_t deltaMs) {
  // serial input handling for player controls
  if (Serial.available()) {
    char command = Serial.read();
    if (command == 'n') {
      player.nextTrack();
      drawCover(state.library[state.queue[state.currentTrackIndex]].cover_path);
    } else if (command == 'p') {
      player.previousTrack();
      drawCover(state.library[state.queue[state.currentTrackIndex]].cover_path);
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
    if (coverBuffer) {
      cover.read((uint8_t*)coverBuffer, 86 * 86 * sizeof(uint16_t));
      canvas.drawRGBBitmap(SCREEN_WIDTH / 2 - 43, SCREEN_HEIGHT / 3 - 38, coverBuffer, 86, 86);
      free(coverBuffer);
    }
  }
  cover.close();
}
