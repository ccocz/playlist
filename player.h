#ifndef PLAYLIST_PLAYER_H
#define PLAYLIST_PLAYER_H

#include "track.h"
#include "player_exception.h"
#include "file.h"
#include "audio.h"
#include "video.h"
#include "playlist.h"
#include <memory>

class Player {
public:
    std::shared_ptr<Track> openFile(File file);
    std::shared_ptr<Playlist> createPlaylist(const std::string &name);
};

#endif //PLAYLIST_PLAYER_H
