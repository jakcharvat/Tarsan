//
//  menu-error.cpp
//  Tarsan
//
//  Created by Jakub Charvát on 12.06.2022.
//

#include "menu-error.hpp"


MenuError::MenuError(std::string message):
_error(std::move(message)) { }



const char *
MenuError::what() const noexcept {
    return _error.c_str();
}
