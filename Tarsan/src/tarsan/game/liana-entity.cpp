//
//  liana-entity.cpp
//  Tarsan
//
//  Created by Jakub Charvát on 12.06.2022.
//

#include "liana-entity.hpp"

#include "../ncurses/color.hpp"


char
LianaEntity::getChar() const {
    attrset(Color::pair(COLOR_GREEN, COLOR_DEFAULT));
    return '|';
}


LianaEntity::LianaEntity(Coord position):
Entity(position) { }
