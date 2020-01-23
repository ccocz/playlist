#ifndef PLAYLIST_PLAYLIST_H
#define PLAYLIST_PLAYLIST_H

#include <iostream>
#include "track.h"
#include "player_exception.h"
#include "mode.h"

class Playlist : public Track {
private:
    std::vector <Track*> list;
    std::string name;
    Mode *mode = new SequenceMode;
public:
    Playlist() = default;
    explicit Playlist(const std::string &name);
    void add(Track *track);
    void add(Track *track, int pos);
    void remove();
    void remove(int pos);
    void play() override;
    bool play(Track *track) override;
    void setMode(Mode *new_mode);
};

#endif //PLAYLIST_PLAYLIST_H
