#ifndef PLAYLIST_MODE_H
#define PLAYLIST_MODE_H

#include <random>
#include <algorithm>
#include <memory>
#include "track.h"

class Mode {
public:
    Mode() = default;
    virtual std::vector <std::shared_ptr<Track>> re_arrange(const std::vector <std::shared_ptr<Track>> &v) = 0;
};

class SequenceMode : public Mode {
public:
    SequenceMode() : Mode() {}
    std::vector <std::shared_ptr<Track>> re_arrange(const std::vector <std::shared_ptr<Track>> &v) override;
};

class ShuffleMode : public Mode {
private:
    int seed;
public:
    explicit ShuffleMode(int x);
    std::vector <std::shared_ptr<Track>> re_arrange(const std::vector <std::shared_ptr<Track>> &v) override;
};

class OddEvenMode : public Mode {
public:
    OddEvenMode() : Mode() {}
  std::vector <std::shared_ptr<Track>> re_arrange(const std::vector <std::shared_ptr<Track>> &v) override;
};

std::shared_ptr<Mode> createSequenceMode();

std::shared_ptr<Mode> createShuffleMode(int seed);

std::shared_ptr<Mode> createOddEvenMode();

#endif //PLAYLIST_MODE_H
