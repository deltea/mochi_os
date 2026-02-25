#include <SD.h>
#include <ArduinoJson.h>
#include "sd.h"
#include "constants.h"
#include "state.h"

// initializes and sets up the sd card reader
void initSD() {
  if (!SD.begin(CARD_CS)) {
    Serial.println("sd read failed, or not present");
    while (1);
  }
  Serial.println("sd card initialized!");
}

// go through the root directory and index everything
// TODO: i lowk don't need this, just call indexPlaylists and indexTracks directly
void indexLibrary() {
  Serial.println("indexing library...");
  File root = SD.open("/");
  if (!root || !root.isDirectory()) {
    Serial.println("failed to open root");
    return;
  }

  File file = root.openNextFile();
  while (file) {
    if (file.isDirectory()) {
      Serial.println("found directory: " + String(file.name()));
      if (String(file.name()) == "playlists") {
        indexPlaylists("/playlists");
      } else if (String(file.name()) == "tracks") {
        indexTracks("/tracks");
      }
    }

    file = root.openNextFile();
  }
}

// go through the tracks directory and index track files
void indexTracks(std::string tracksDir) {
  Serial.println("indexing tracks...");
  File dir = SD.open(tracksDir.c_str());
  if (!dir || !dir.isDirectory()) {
    Serial.println("failed to open tracks directory");
    return;
  }

  File file = dir.openNextFile();
  while (file) {
    if (!file.isDirectory()) {
      Serial.println("found track: " + String(file.name()));
      Track track = getTrackFromPath((tracksDir + "/" + file.name()).c_str());
      state.library[file.name()] = track;
    }

    file = dir.openNextFile();
  }
  Serial.println("done indexing tracks");
}

// go through the playlists directory and index playlist files
void indexPlaylists(std::string playlistDir) {
  Serial.println("indexing playlists...");
  File dir = SD.open(playlistDir.c_str());
  if (!dir || !dir.isDirectory()) {
    Serial.println("failed to open playlist directory");
    return;
  }

  File file = dir.openNextFile();
  while (file) {
    if (!file.isDirectory()) {
      Serial.println("found playlist: " + String(file.name()));
      Playlist playlist = getPlaylistFromPath((playlistDir + "/" + file.name()).c_str());
      state.playlists.push_back(playlist);
    }

    file = dir.openNextFile();
  }
  Serial.println("done indexing playlists");
}

// returns a track object from a path
Track getTrackFromPath(const char *path) {
  File jsonFile = SD.open(("/tracks/" + String(path) + "/track.json").c_str());
  if (!jsonFile) {
    Serial.println("failed to open track file: " + String(path));
    return Track();
  }

  JsonDocument doc;
  DeserializationError error = deserializeJson(doc, jsonFile);
  if (error) {
    Serial.println("failed to parse track json: " + String(error.c_str()));
    jsonFile.close();
    return Track();
  }

  Track track;
  track.title = doc["title"].as<std::string>();
  track.artist = doc["artist"].as<std::string>();
  // convert from seconds to ms
  track.duration_ms = doc["duration"].as<uint32_t>() * 1000;
  track.color = doc["color"].as<uint32_t>();
  track.cover_path = ("/tracks/" + String(path) + "/cover.raw").c_str();
  track.audio_path = ("/tracks/" + String(path) + "/audio.mp3").c_str();

  jsonFile.close();
  return track;
}

// returns a playlist object from a path
Playlist getPlaylistFromPath(const char *path) {
  File jsonFile = SD.open(path);
  if (!jsonFile) {
    Serial.println("failed to open playlist file: " + String(path));
    jsonFile.close();
    return Playlist();
  }

  JsonDocument doc;
  DeserializationError error = deserializeJson(doc, jsonFile);
  if (error) {
    Serial.println("failed to parse playlist json: " + String(error.c_str()));
    jsonFile.close();
    return Playlist();
  }

  Playlist playlist;
  playlist.name = doc["name"].as<std::string>();
  JsonArray tracks = doc["tracks"].as<JsonArray>();
  for (JsonVariant track : tracks) {
    playlist.tracks.push_back(track.as<std::string>());
  }

  jsonFile.close();
  return playlist;
}
