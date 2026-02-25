#pragma once

#include <map>
#include <string>
#include <vector>

struct Track {
  std::string title;
  std::string artist;
  uint32_t duration_ms;
  uint16_t color;
  std::string cover_path;
  std::string audio_path;
};

struct Playlist {
  std::string name;
  std::vector<std::string> tracks;
};

struct State {
public:
  std::map<std::string, Track> library;
  std::vector<std::string> queue;
  std::vector<Playlist> playlists;

  int currentTrackIndex = 0;
  uint32_t playbackPositionMs = 0;

  // TODO: actuallyuse this volume
  int volume = 50;
  bool isPlaying = false;

  void nextTrack();
  void previousTrack();
  void addToQueue(std::string trackName);
  void addPlaylistToQueue(Playlist playlist);
};

extern State state;
