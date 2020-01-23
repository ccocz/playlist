#ifndef PLAYLIST_VIDEO_H
#define PLAYLIST_VIDEO_H

#include <algorithm>
#include <iostream>
#include "track.h"

class Video : public Track {
private:
    std::string title;
    std::string year;
    std::string content;
    static void decode(const std::string &s);
public:
    explicit Video(const std::string &name);
    void play() override;
    bool play(Track *track) override;
};

#endif //PLAYLIST_VIDEO_H
