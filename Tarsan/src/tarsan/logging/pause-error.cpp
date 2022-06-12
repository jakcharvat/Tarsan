//
//  pause-error.cpp
//  Tarsan
//
//  Created by Jakub Charvát on 12.06.2022.
//

#include "pause-error.hpp"


PauseError::PauseError(std::string message):
_error(std::move(message)) { }



const char *
PauseError::what() const noexcept {
    return _error.c_str();
}

