#pragma once

#include <Adafruit_VS1053.h>
#include "core/state.h"

extern Adafruit_VS1053_FilePlayer p;

struct Player {
public:
  void init();
  void feed();
  void playFile(std::string path);
  void playTrack(Track track);
  void nextTrack();
  void previousTrack();
};

extern Player player;
