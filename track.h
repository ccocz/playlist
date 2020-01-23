#ifndef PLAYLIST_TRACK_H
#define PLAYLIST_TRACK_H

#include <sstream>
#include <string>
#include <vector>

class Track {
private:
    std::vector<std::string> tokens;
public:
    virtual void play() = 0;
    virtual bool play(Track*) = 0;
    Track() = default;
    std::vector<std::string> &get_tokens();
    explicit Track(const std::string &description);
};
#endif //PLAYLIST_TRACK_H
