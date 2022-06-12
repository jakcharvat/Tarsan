//
//  fatal-error.cpp
//  Tarsan
//
//  Created by Jakub Charvát on 12.06.2022.
//

#include "fatal-error.hpp"


FatalError::FatalError(std::string message):
_error(std::move(message)) { }



const char *
FatalError::what() const noexcept {
    return _error.c_str();
}
