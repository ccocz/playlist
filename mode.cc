#include "mode.h"
#include <memory>

std::vector <std::shared_ptr<Track>> SequenceMode::re_arrange(const std::vector <std::shared_ptr<Track>> &v) {
    return v;
}

ShuffleMode::ShuffleMode(int x) {
    seed = x;
}

std::vector <std::shared_ptr<Track>> ShuffleMode::re_arrange(const std::vector <std::shared_ptr<Track>> &v) {
    std::vector <std::shared_ptr<Track>> ordered = v;
    std::shuffle(ordered.begin(), ordered.end(), std::default_random_engine(seed));
    return ordered;
}

std::vector <std::shared_ptr<Track>> OddEvenMode::re_arrange(const std::vector <std::shared_ptr<Track>> &v) {
    std::vector <std::shared_ptr<Track>> ordered;
    for (size_t i = 1; i < v.size(); i += 2) {
        ordered.push_back(v[i]);
    }
    for (size_t i = 0; i < v.size(); i += 2) {
        ordered.push_back(v[i]);
    }
    return ordered;
}

std::shared_ptr<Mode>createSequenceMode() {
    return std::make_shared<SequenceMode>();
}

std::shared_ptr<Mode> createShuffleMode(int seed) {
    return std::make_shared<ShuffleMode>(ShuffleMode(seed));
}

std::shared_ptr<Mode> createOddEvenMode() {
    return std::make_shared<OddEvenMode>();
}
