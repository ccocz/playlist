#include "video.h"

void Video::decode(const std::string &s) {
    for (char i : s) {
        if (isalpha(i)) {
          bool upper = isupper(i);
          unsigned char c = tolower(i);
          c += 13;
          c -= 26 * (c > 'z');
          if (upper) {
            std::cout << (char) toupper(c);
          } else {
            std::cout << c;
          }
        } else {
          std::cout << i;
        }
    }
}

Video::Video(const std::string &name) : Track(name) {
    auto tokens = get_tokens();
    title = *(std::find(tokens.begin(), tokens.end(), "title") + 1);
    year = *(std::find(tokens.begin(), tokens.end(), "year") + 1);
    content = tokens.back();
}

void Video::play() {
    std:: cout << "Video [" << title << ", " << year << "]: ";
    decode(content);
    std::cout << std::endl;
}

bool Video::play(Track *track) {
    return this == track;
}
