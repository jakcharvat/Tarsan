//
//  entity.cpp
//  Tarsan
//
//  Created by Jakub Charvát on 12.06.2022.
//

#include "entity.hpp"

#include "../ncurses/color.hpp"

#include "map.hpp"


Entity::Entity(Coord position):
position(position) { }


void
Entity::update(Map &) { }


bool
Entity::_isOnGround(Map &map) const {
    return map.raycast(position, Map::RaycastDirection::DOWN, 1) == 0;
}


void
Entity::draw(WINDOW *window) const {
    wmove(window, position.y, position.x);
    wattrset(window, Color::pair(COLOR_WHITE, COLOR_DEFAULT));
    wprintw(window, "%c", _getChar(window));
}
