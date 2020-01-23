#include "playlist.h"

Playlist::Playlist(const std::string &name) : Track(name) {
    this->name = name;
}

void Playlist::add(Track *track) {
    if (!(track->play(this))) {
        list.push_back(track);
    } else {
        throw PlayerException("cycle detected");
    }
}

void Playlist::add(Track *track, int pos) {
    if (!(track->play(this))) {
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

bool Playlist::play(Track *track) {
    bool found = false;
    for (auto x : mode->re_arrange(list)) {
        found |= (x == track);
        found |= x->play(track);
    }
    return found;
}

void Playlist::setMode(Mode *new_mode) {
    mode = new_mode;
}


