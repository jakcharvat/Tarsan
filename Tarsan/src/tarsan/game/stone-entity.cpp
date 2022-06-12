//
//  stone-entity.cpp
//  Tarsan
//
//  Created by Jakub Charvát on 12.06.2022.
//

#include "stone-entity.hpp"

#include "../ncurses/color.hpp"


char
StoneEntity::_getChar(WINDOW * window) const {
    if (window) {
        wattrset(window, Color::pair(COLOR_MAGENTA, COLOR_DEFAULT));
    }
    return '*';
}


StoneEntity::StoneEntity(Coord position):
Entity(std::move(position), RaycastLayer::STONE) { }
