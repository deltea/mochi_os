#pragma once

#include "core/state.h"

struct Card {
public:
  void init();
  void indexLibrary();
  void indexPlaylists(std::string playlistDir);
  void indexTracks(std::string tracksDir);
  Track getTrackFromPath(std::string path);
  Playlist getPlaylistFromPath(std::string path);
};

extern Card sd;
