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
    wattrset(window, Color::pair(COLOR_WHITE, COLOR_DEFAULT));
    wprintw(window, "%c", getChar(window));
}
