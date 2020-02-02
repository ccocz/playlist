#ifndef PLAYLIST_PLAYLIST_H
#define PLAYLIST_PLAYLIST_H

#include <iostream>
#include <memory>
#include "track.h"
#include "player_exception.h"
#include "mode.h"

class Playlist : public Track {
private:
    std::vector <std::shared_ptr<Track>> list;
    std::string name;
    std::shared_ptr <Mode> mode = std::make_shared<SequenceMode>();
public:
    Playlist() = default;
    explicit Playlist(const std::string &name);
    void add(const std::shared_ptr<Track> &track);
    void add(const std::shared_ptr<Track> &track, int pos);
    void remove();
    void remove(int pos);
    void play() override;
    bool play(const std::shared_ptr<Track> &track) override;
    void setMode(const std::shared_ptr<Mode> &mode);
};

#endif //PLAYLIST_PLAYLIST_H
