#include "state.h"

State state;

void State::nextTrack() {
  if (currentTrackIndex < queue.size() - 1) {
    currentTrackIndex++;
  }
}

void State::previousTrack() {
  if (currentTrackIndex > 0) {
    currentTrackIndex--;
  }
}

void State::addToQueue(std::string trackName) {
  queue.push_back(trackName);
}

void State::addPlaylistToQueue(Playlist playlist) {
  for (std::string trackPath : playlist.tracks) {
    queue.push_back(trackPath);
  }
}
