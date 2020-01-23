#include "player_exception.h"

const char *PlayerException::what() const noexcept {
    return error.c_str();
}

PlayerException::PlayerException(std::string message) {
    error = std::move(message);
}
