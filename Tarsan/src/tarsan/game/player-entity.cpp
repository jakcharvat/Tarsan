//
//  player-entity.cpp
//  Tarsan
//
//  Created by Jakub Charvát on 12.06.2022.
//

#include "player-entity.hpp"

#include "../ncurses/color.hpp"


char
PlayerEntity::getChar(WINDOW * window) const {
    wattrset(window, Color::pair(COLOR_GREEN, COLOR_DEFAULT));
    return '>';
}


PlayerEntity::PlayerEntity(Coord position):
Entity(position) { }
