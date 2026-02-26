#include "audio.h"
#include <constants.h>

Adafruit_VS1053_FilePlayer p(VS1053_RESET, VS1053_CS, VS1053_DCS, VS1053_DREQ, CARD_CS);
Player player;

void Player::init() {
  if (!p.begin()) {
    Serial.println("couldn't find vs1053, do you have the right pins defined?");
    while (1);
  }
  Serial.println("player initialized!");

  // higher number means quieter for some reason
  p.setVolume(65, 65);
  // p.sineTest(0x22, 200);
}

void Player::playFile(std::string path) {
  p.startPlayingFile(path.c_str());
}

void Player::playTrack(Track track) {
  Serial.println(track.audio_path.c_str());
  playFile(track.audio_path);
}

void Player::feed() {
  p.feedBuffer();
}
