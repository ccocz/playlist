#include "player.h"

Track *Player::openFile(File file) {
    if (file.isCorrupt()) {
        throw PlayerException("corrupt file");
    }
    else if (file.isAudio()) {
        if (file.isContentCorrupt()) {
            throw PlayerException("corrupt content");
        }
        return new Audio(file.getDescription());
    } else if (file.isVideo()) {
        if (file.isContentCorrupt()) {
            throw PlayerException("corrupt content");
        }
        return new Video(file.getDescription());
    }
    throw PlayerException("unsupported type");
}

Playlist *Player::createPlaylist(const std::string &name) {
    return new Playlist(name);
}
