//
//  lava-entity.cpp
//  Tarsan
//
//  Created by Jakub Charvát on 12.06.2022.
//

#include "lava-entity.hpp"

#include "../ncurses/color.hpp"


char
LavaEntity::getChar() const {
    attrset(Color::pair(COLOR_RED, COLOR_DEFAULT));
    return '#';
};
