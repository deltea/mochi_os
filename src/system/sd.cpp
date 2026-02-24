#include <SD.h>
#include "sd.h"
#include "constants.h"
#include <state.h>

void initSD() {
  if (!SD.begin(CARD_CS)) {
    Serial.println("sd read failed, or not present");
    while (1);
  }
  Serial.println("sd card initialized!");
}

void listPlaylists() {
  File root = SD.open("/");
  if (!root || !root.isDirectory()) {
    Serial.println("failed to open root");
    return;
  }

  File file = root.openNextFile();
  while (file) {
    if (file.isDirectory()) {
      Serial.println("found directory: " + String(file.name()));
    }

    file = root.openNextFile();
  }
  Serial.println("done listing");
}

// Track getTrackFromPath(const char *path) {
//   Track track;
//   File jsonFile = SD.open(path);
//   if (!jsonFile) {
//     Serial.println("failed to open track file: " + String(path));
//     return Track();
//   }

//   return track;
// }
