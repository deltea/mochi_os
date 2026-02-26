#include "playback.h"
#include <SD.h>
#include "constants.h"
#include "system/display.h"
#include "system/audio.h"
#include "system/sd.h"
#include "core/state.h"
#include "sd.h"

void playTrack(Track track) {
  playFile(track.audio_path.c_str());
}

void play() {
  playTrack(getTrackFromPath(state.queue[state.currentTrackIndex].c_str()));
}

void nextTrack() {
  state.nextTrack();
  playTrack(getTrackFromPath(state.queue[state.currentTrackIndex].c_str()));
}

void previousTrack() {
  state.previousTrack();
  playTrack(getTrackFromPath(state.queue[state.currentTrackIndex].c_str()));
}
