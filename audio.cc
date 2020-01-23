#include "audio.h"

Audio::Audio(const std::string &name) : Track(name) {
    auto tokens = get_tokens();
    artist = *(std::find(tokens.begin(), tokens.end(), "artist") + 1);
    title = *(std::find(tokens.begin(), tokens.end(), "title") + 1);
    content = tokens.back();
}

void Audio::play() {
    auto tokens = get_tokens();
    std::cout << "Audio [" << artist << ", " << title << "]: " << content << std::endl;
}

bool Audio::play(Track *track) {
    return false;
}

