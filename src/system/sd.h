#pragma once

#include "state.h"

void initSD();
void indexLibrary();
void indexPlaylists(std::string playlistDir);
void indexTracks(std::string tracksDir);
Track getTrackFromPath(const char* path);
Playlist getPlaylistFromPath(const char* path);
