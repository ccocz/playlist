#include "playlist.h"
#include <memory>

Playlist::Playlist(const std::string &name) : Track(name) {
    this->name = name;
}

void Playlist::add(const std::shared_ptr<Track> &track) {
    if (track.get() != this && !(track->play(shared_from_this()))) {
        list.push_back(track);
    } else {
        throw PlayerException("cycle detected");
    }
}

void Playlist::add(const std::shared_ptr<Track> &track, int pos) {
  if (!(track->play(shared_from_this()))) {
        list.insert(list.begin() + pos, track);
    } else {
        throw PlayerException("cycle detected");
    }
}

void Playlist::remove() {
    list.pop_back();
}

void Playlist::remove(int pos) {
    list.erase(list.begin() + pos);
}

void Playlist::play() {
    std::cout << "Playlist [" << name << "]\n";
    for (auto x : mode->re_arrange(list)) {
        x->play();
    }
}

bool Playlist::play(const std::shared_ptr<Track> &track) {
    bool found = false;
    for (auto x : mode->re_arrange(list)) {
        found |= (x == track);
        found |= x->play(track);
    }
    return found;
}

void Playlist::setMode(const std::shared_ptr<Mode> &new_mode) {
    mode = new_mode;
}