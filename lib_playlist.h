#ifndef PLAYLIST_LIB_PLAYLIST_H
#define PLAYLIST_LIB_PLAYLIST_H

#include <string>
#include <vector>
#include <sstream>
#include <list>
#include <algorithm>
#include <random>

//todo: watch for const refs

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
  virtual void play() = 0;
  Track() = default;
  std::vector<std::string> &get_tokens() {
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
private:
  std::string artist;
  std::string title;
  std::string content;
public:
  explicit Song(const std::string &name) : Track(name) {
    auto tokens = get_tokens();
    artist = *(std::find(tokens.begin(), tokens.end(), "artist") + 1);
    title = *(std::find(tokens.begin(), tokens.end(), "title") + 1);
    content = tokens.back();
  }
  void play() override {
    auto tokens = get_tokens();
    std::cout << "Song [" << artist << ", " << title << "]: " << content << std::endl;
  }
};

class Movie : public Track {
private:
  std::string title;
  std::string year;
  std::string content;
  static void decode(const std::string &s) {
    for (char i : s) {
      bool upper = isupper(i);
      unsigned char c = tolower(i);
      c += 13;
      c -= 26 * (c > 'z');
      if (upper) {
        std::cout << (char)toupper(c);
      } else {
        std::cout << c;
      }
    }
  }
public:
  explicit Movie(const std::string &name) : Track(name) {
    auto tokens = get_tokens();
    title = *(std::find(tokens.begin(), tokens.end(), "title") + 1);
    year = *(std::find(tokens.begin(), tokens.end(), "year") + 1);
    content = tokens.back();
  }
  void play() override {
    std:: cout << "Movie [" << title << ", " << year << "]: ";
    decode(content);
    std::cout << std::endl;
  }
};

class Mode {
public:
  Mode() = default;
  virtual std::vector <Track*> re_arrange(const std::vector <Track*> &v) = 0;
};

class SequenceMode : public Mode {
public:
  SequenceMode() = default;
  std::vector <Track*> re_arrange(const std::vector <Track*> &v) override {
    return v;
  }
};

class ShuffleMode : public Mode {
private:
  int seed;
public:
  explicit ShuffleMode(int x) {
    seed = x;
  }
  std::vector <Track*> re_arrange(const std::vector <Track*> &v) override {
    std::vector <Track*> ordered = v;
    std::shuffle(ordered.begin(), ordered.end(), std::default_random_engine(seed));
    return ordered;
  }
};

//todo:not reference
class OddEvenMode : public Mode {
public:
  OddEvenMode() = default;
  std::vector <Track*> re_arrange(const std::vector <Track*> &v) override {
    std::vector <Track*> ordered;
    for (int i = 1; i < v.size(); i += 2) {
      ordered.push_back(v[i]);
    }
    for (int i = 0; i < v.size(); i += 2) {
      ordered.push_back(v[i]);
    }
    return ordered;
  }
};

//todo : omit attributes of track
//todo: maybe friends?
//todo: cycle

Mode *createSequenceMode() {
  return new SequenceMode;
}

Mode *createShuffleMode(int seed) {
  return new ShuffleMode(seed);
}

Mode *createOddEvenMode() {
  return new OddEvenMode;
};

class Playlist : public Track {
private:
  std::vector <Track*> list;
  std::string name;
  Mode *mode = new SequenceMode;
public:
  Playlist() = default;
  explicit Playlist(const std::string &name) {
    this->name = name;
  }
  void add(Track *track) {
    list.push_back(track);
  }
  void add(Track *track, int pos) {
    list.insert(list.begin() + pos, track);
  }
  void remove() {
    list.pop_back();
  }
  void remove(int pos) {
    list.erase(list.begin() + pos);
  }
  void play() override {
    std::cout << "Playlist [" << name << "]\n";
    for (auto x : mode->re_arrange(list)) {
      x->play();
    }
  }
  void setMode(Mode *new_mode) {
    mode = new_mode;
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
