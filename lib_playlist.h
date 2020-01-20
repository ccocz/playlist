#ifndef PLAYLIST_LIB_PLAYLIST_H
#define PLAYLIST_LIB_PLAYLIST_H

#include <string>
#include <vector>
#include <sstream>

class PlayerException {
public:
  [[nodiscard]] std::string what() const {
    return std::__cxx11::string();
  }
};

class Track {
private:
  std::vector<std::string> tokens;
public:
  virtual void play() {
  }
  Track() = default;
  std::vector<std::string> get_tokens() {
    return tokens;
  }
  explicit Track(const std::string &description) {
    std::string token;
    std::istringstream tokenStream(description);
    while (std::getline(tokenStream, token, '|')) {
      tokens.push_back(token);
    }
  }
};

class Song : public Track {
public:
  explicit Song(const std::string &name) : Track(name){}
  void play() override {
  }
};

class Movie : public Track {
public:
  explicit Movie(const std::string &name) : Track(name) {}
  void play() override {

  }
};

class File {
private:
  std::string description;
public:
  explicit File(const std::string &name) {
    description = name;
  }
  bool isAudio() {
    return description[0] == 'a';
  }
  std::string getDescription() {
    return description;
  }
};

class Playlist {
public:
  Playlist() = default;
  void add(Track *track) {

  }
  void add(Playlist *playlist) {

  }
  void add(Track *track, int pos) {

  }
  void remove() {

  }
  void remove(int pos) {

  }
  void play() {

  }
};

class Player {
public:
  Track *openFile(File file) {
    if (file.isAudio()) {
      return new Song(file.getDescription());
    } else {
      return new Movie(file.getDescription());
    }
  }
  Playlist *createPlaylist(const std::string &name) {
    return new Playlist;
  }
};

#endif //PLAYLIST_LIB_PLAYLIST_H
