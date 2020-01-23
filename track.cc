#include "track.h"

std::vector<std::string> &Track::get_tokens() {
    return tokens;
}

Track::Track(const std::string &description) {
    std::string token;
    std::string element;
    std::istringstream tokenStream(description);
    while (std::getline(tokenStream, token, '|')) {
        std::istringstream lineStream(token);
        while (std::getline(lineStream, element, ':')) {
            tokens.push_back(element);
        }
    }
}
