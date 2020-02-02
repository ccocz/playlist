#include "player.h"
#include <memory>

std::shared_ptr<Track> Player::openFile(File file) {
    if (file.isCorrupt()) {
        throw PlayerException("corrupt file");
    }
    else if (file.isAudio()) {
        if (file.isContentCorrupt()) {
            throw PlayerException("corrupt content");
        }
        return std::make_shared <Audio> (file.getDescription());
    } else if (file.isVideo()) {
        if (file.isContentCorrupt()) {
            throw PlayerException("corrupt content");
        }
        return std::make_shared <Video> (file.getDescription());
    }
    throw PlayerException("unsupported type");
}

std::shared_ptr<Playlist> Player::createPlaylist(const std::string &name) {
  return std::make_shared<Playlist>(name);
}
