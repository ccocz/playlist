#ifndef PLAYLIST_FILE_H
#define PLAYLIST_FILE_H

#include <string>

class File {
private:
    std::string description;
    const std::string valid = ",.!?':;-";
public:
    explicit File(const std::string &name);
    bool isCorrupt();
    bool isAudio();
    bool isVideo();
    bool isContentCorrupt();
    std::string getDescription();
};

#endif //PLAYLIST_FILE_H
