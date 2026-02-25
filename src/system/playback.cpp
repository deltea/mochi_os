#include "playback.h"
#include <constants.h>
#include <SD.h>
#include "display.h"
#include "audio.h"
#include "state.h"

void playTrack(Track track) {
  playFile(track.audio_path.c_str());
  // drawCover(track.cover_path);
}
