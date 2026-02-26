#include "player_screen.h"
#include "constants.h"
#include "system/display.h"
#include "system/card.h"
#include "system/audio.h"
#include "assets/fonts/monogram.h"

void PlayerScreen::init(State &state) {
  state.addPlaylistToQueue(state.playlists[3]);
  player.playTrack(state.library[state.queue[state.currentTrackIndex]]);
  updateTrack();
}

void PlayerScreen::update(State &state, uint32_t deltaMs) {
  // serial input handling for player controls
  if (Serial.available()) {
    char command = Serial.read();
    if (command == 'n') {
      player.nextTrack();
      updateTrack();
    } else if (command == 'p') {
      player.previousTrack();
      updateTrack();
    }
  }
}

void PlayerScreen::render(State &state) {
  // canvas.fillScreen(BG);
}

void PlayerScreen::updateTrack() {
  display.clear();
  drawCover(state.library[state.queue[state.currentTrackIndex]].cover_path);
  display.drawText(state.library[state.queue[state.currentTrackIndex]].title.c_str(), SCREEN_WIDTH / 2, SCREEN_HEIGHT - 2 - 20, true, &monogram8pt7b, FG);
  display.drawText(state.library[state.queue[state.currentTrackIndex]].artist.c_str(), SCREEN_WIDTH / 2, SCREEN_HEIGHT - 2 - 20 + 8, true, &monogram8pt7b, FG);
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
