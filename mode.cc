#include "mode.h"

std::vector<Track *> SequenceMode::re_arrange(const std::vector<Track *> &v) {
    return v;
}

ShuffleMode::ShuffleMode(int x) {
    seed = x;
}

std::vector<Track *> ShuffleMode::re_arrange(const std::vector<Track *> &v) {
    std::vector <Track*> ordered = v;
    std::shuffle(ordered.begin(), ordered.end(), std::default_random_engine(seed));
    return ordered;
}

std::vector<Track *> OddEvenMode::re_arrange(const std::vector<Track *> &v) {
    std::vector <Track*> ordered;
    for (size_t i = 1; i < v.size(); i += 2) {
        ordered.push_back(v[i]);
    }
    for (size_t i = 0; i < v.size(); i += 2) {
        ordered.push_back(v[i]);
    }
    return ordered;
}

Mode *createSequenceMode() {
    return new SequenceMode;
}

Mode *createShuffleMode(int seed) {
    return new ShuffleMode(seed);
}

Mode *createOddEvenMode() {
    return new OddEvenMode;
}
