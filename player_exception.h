#ifndef INSERTION_ORDERED_MAP_PLAYER_EXCEPTION_H
#define INSERTION_ORDERED_MAP_PLAYER_EXCEPTION_H

#include <string>

class PlayerException : std::exception {
private:
    std::string error;
public:
    [[nodiscard]] const char * what() const noexcept override;
    explicit PlayerException(std::string message);
};

#endif //PLAYLIST_PLAYER_EXCEPTION_H
