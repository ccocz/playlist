#ifndef PLAYLIST_MODE_H
#define PLAYLIST_MODE_H

#include <random>
#include <algorithm>
#include "track.h"

class Mode {
public:
    Mode() = default;
    virtual std::vector <Track*> re_arrange(const std::vector <Track*> &v) = 0;
};

class SequenceMode : public Mode {
public:
    SequenceMode() : Mode() {}
    std::vector <Track*> re_arrange(const std::vector <Track*> &v) override;
};

class ShuffleMode : public Mode {
private:
    int seed;
public:
    explicit ShuffleMode(int x);
    std::vector <Track*> re_arrange(const std::vector <Track*> &v) override;
};

class OddEvenMode : public Mode {
public:
    OddEvenMode() : Mode() {}
    std::vector <Track*> re_arrange(const std::vector <Track*> &v) override;
};

Mode *createSequenceMode();

Mode *createShuffleMode(int seed);

Mode *createOddEvenMode();

#endif //PLAYLIST_MODE_H
