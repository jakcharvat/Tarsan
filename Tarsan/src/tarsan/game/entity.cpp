//
//  entity.cpp
//  Tarsan
//
//  Created by Jakub Charvát on 12.06.2022.
//

#include "entity.hpp"

#include "../ncurses/color.hpp"


Entity::Entity(Coord position):
coord(position) { }


void
Entity::draw(WINDOW *window) const {
    wmove(window, coord.y, coord.x);
    attrset(Color::pair(COLOR_WHITE, COLOR_DEFAULT));
    printw("%c", getChar());
}
