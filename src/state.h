#pragma once

#include <string>
#include <vector>

struct Track {
  std::string name;
  std::string artist;
  uint32_t duration_ms;
};

struct State {
public:
  std::vector<Track> library;
  std::vector<int> queue;

  int currentTrackIndex = 0;
  uint32_t playbackPositionMs = 0;

  int volume = 50;
  bool isPlaying = false;

  void nextTrack();
  void previousTrack();
};
