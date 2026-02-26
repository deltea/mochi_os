#pragma once

#include <Adafruit_VS1053.h>
#include "core/state.h"

extern Adafruit_VS1053_FilePlayer p;

struct Player {
public:
  void init();
  void playFile(std::string path);
  void playTrack(Track track);
  void feed();
};

extern Player player;
