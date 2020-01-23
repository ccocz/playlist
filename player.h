#ifndef PLAYLIST_PLAYER_H
#define PLAYLIST_PLAYER_H

#include "track.h"
#include "player_exception.h"
#include "file.h"
#include "audio.h"
#include "video.h"
#include "playlist.h"

class Player {
public:
    Track *openFile(File file);
    Playlist *createPlaylist(const std::string &name);
};

#endif //PLAYLIST_PLAYER_H
