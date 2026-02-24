#include "audio.h"
#include <constants.h>

Adafruit_VS1053_FilePlayer player(VS1053_RESET, VS1053_CS, VS1053_DCS, VS1053_DREQ, CARD_CS);

void initAudio() {
  if (!player.begin()) {
    Serial.println("couldn't find vs1053, do you have the right pins defined?");
    while (1);
  }
  Serial.println("player initialized!");

  player.setVolume(60, 60);
  // player.useInterrupt(VS1053_FILEPLAYER_TIMER0_INT);
  // player.sineTest(0x22, 200);
}

void playFile(const char* path) {
  player.playFullFile(path);
}
