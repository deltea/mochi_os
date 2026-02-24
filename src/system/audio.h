#pragma once

#include <Adafruit_VS1053.h>

extern Adafruit_VS1053_FilePlayer player;

void initAudio();
void playFile(const char* path);
void feedPlayer();
