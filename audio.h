#ifndef PLAYLIST_AUDIO_H
#define PLAYLIST_AUDIO_H

#include <iostream>
#include "track.h"

class Audio : public Track {
private:
    std::string artist;
    std::string title;
    std::string content;
public:
    explicit Audio(const std::string &name);
    void play() override;
    bool play(Track *track) override;
};

#endif //PLAYLIST_AUDIO_H
