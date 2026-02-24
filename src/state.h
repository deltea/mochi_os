#pragma once

#include <string>
#include <vector>

struct Track {
  std::string name;
  std::string artist;
  std::string cover_path;
  std::string audio_path;
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
