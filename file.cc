#include "file.h"

File::File(const std::string &name) {
    description = name;
}

bool File::isCorrupt() {
    return std::count(description.begin(), description.end(), '|') < 2;
}

bool File::isAudio() {
    return description.substr(0, description.find('|')) == "audio";
}

bool File::isVideo() {
    return description.substr(0, description.find('|')) == "video";
}

bool File::isContentCorrupt() {
    for (int i = (int)description.size() - 1; i >= 0 && description[i] != '|'; i--) {
        if (!isalpha(description[i]) && !isdigit(description[i]) && valid.find(description[i]) == std::string::npos
            && !std::isspace(description[i])) {
            return true;
        }
    }
    return false;
}

std::string File::getDescription() {
    return description;
}
