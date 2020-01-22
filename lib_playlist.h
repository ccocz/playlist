#ifndef PLAYLIST_LIB_PLAYLIST_H
#define PLAYLIST_LIB_PLAYLIST_H

#include <string>
#include <vector>
#include <sstream>
#include <list>
#include <algorithm>
#include <random>

//todo: watch for const refs
//todo: not reference
//todo: cycle

class PlayerException : std::exception {
private:
  std::string error;
public:
  [[nodiscard]] const char * what() const noexcept override {
    return error.c_str();
  }
  explicit PlayerException(const std::string &message) {
    error = message;
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

class Audio : public Track {
private:
  std::string artist;
  std::string title;
  std::string content;
public:
  explicit Audio(const std::string &name) : Track(name) {
    auto tokens = get_tokens();
    artist = *(std::find(tokens.begin(), tokens.end(), "artist") + 1);
    title = *(std::find(tokens.begin(), tokens.end(), "title") + 1);
    content = tokens.back();
  }
  void play() override {
    auto tokens = get_tokens();
    std::cout << "Audio [" << artist << ", " << title << "]: " << content << std::endl;
  }
};

class Video : public Track {
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
  explicit Video(const std::string &name) : Track(name) {
    auto tokens = get_tokens();
    title = *(std::find(tokens.begin(), tokens.end(), "title") + 1);
    year = *(std::find(tokens.begin(), tokens.end(), "year") + 1);
    content = tokens.back();
  }
  void play() override {
    std:: cout << "Video [" << title << ", " << year << "]: ";
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
  const std::string valid = ",.!?':;-";
public:
  explicit File(const std::string &name) {
    description = name;
  }
  bool isCorrupt() {
    return std::count(description.begin(), description.end(), '|') < 2;
  }
  bool isAudio() {
    return description.substr(0, description.find('|')) == "audio";
  }
  bool isVideo() {
    return description.substr(0, description.find('|')) == "video";
  }
  bool isContentCorrupt() {
    for (int i = (int)description.size() - 1; i >= 0 && description[i] != '|'; i--) {
      if (!isalpha(description[i]) && !isdigit(description[i]) && valid.find(description[i]) == std::string::npos
          && !std::isspace(description[i])) {
        return true;
      }
    }
    return false;
  }
  std::string getDescription() {
    return description;
  }
};

class Player {
public:
  Track *openFile(File file) {
    if (file.isCorrupt()) {
      throw PlayerException("corrupt file");
    }
    else if (file.isAudio()) {
      if (!file.isContentCorrupt()) {
        return new Audio(file.getDescription());
      } else {
        throw PlayerException("corrupt content");
      }
    } else if (file.isVideo()) {
      if (!file.isContentCorrupt()) {
        return new Video(file.getDescription());
      } else {
        throw PlayerException("corrupt content");
      }
    } else {
      throw PlayerException("unsupported type");
    }
  }
  Playlist *createPlaylist(const std::string &name) {
    return new Playlist(name);
  }
};

#endif //PLAYLIST_LIB_PLAYLIST_H
