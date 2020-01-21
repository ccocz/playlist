#ifndef PLAYLIST_LIB_PLAYLIST_H
#define PLAYLIST_LIB_PLAYLIST_H

#include <string>
#include <vector>
#include <sstream>
#include <list>
#include <algorithm>

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
    std::string element;
    std::istringstream tokenStream(description);
    while (std::getline(tokenStream, token, '|')) {
      std::istringstream lineStream(token);
      while (std::getline(lineStream, element, ':')) {
        tokens.push_back(element);
      }
    }
  }
};

class Song : public Track {
public:
  explicit Song(const std::string &name) : Track(name){}
  void play() override {
    auto tokens = get_tokens();
    std::string artist = *(std::find(tokens.begin(), tokens.end(), "artist") + 1);
    std::string title = *(std::find(tokens.begin(), tokens.end(), "title") + 1);
    std::cout << "Song [" << artist << ", " << title << "]: " << tokens.back() << std::endl;
  }
};

//todo: apply RTO13
class Movie : public Track {
public:
  explicit Movie(const std::string &name) : Track(name) {}
  void play() override {
    auto tokens = get_tokens();
    auto title = *(std::find(tokens.begin(), tokens.end(), "title") + 1);
    auto year = *(std::find(tokens.begin(), tokens.end(), "year") + 1);
    std:: cout << "Movie [" << title << ", " << year << "]: " << tokens.back() << std::endl;
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

//todo : ommit attributes of track
class Playlist : public Track {
private:
  std::list <Track*> list;
  std::string name;
public:
  Playlist() = default;
  explicit Playlist(const std::string &name) {
    this->name = name;
  }
  void add(Track *track) {
    list.push_back(track);
  }
  void add(Track *track, int pos) {
    auto it = list.begin();
    std::advance(it, pos);
    list.insert(it, track);
  }
  void remove() {
    list.pop_back();
  }
  void remove(int pos) {
    auto it = list.begin();
    std::advance(it, pos);
    list.erase(it);
  }
  void play() override {
    std::cout << "Playlist [" << name << "]\n";
    for (auto track : list) {
      track->play();
    }
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
    return new Playlist(name);
  }
};

#endif //PLAYLIST_LIB_PLAYLIST_H
