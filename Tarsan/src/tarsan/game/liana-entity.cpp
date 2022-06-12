//
//  liana-entity.cpp
//  Tarsan
//
//  Created by Jakub Charvát on 12.06.2022.
//

#include "liana-entity.hpp"

#include "../ncurses/color.hpp"

#include "map.hpp"


char
LianaEntity::_getChar(WINDOW * window) const {
    wattrset(window, Color::pair(COLOR_GREEN, COLOR_DEFAULT));
    return '|';
}


LianaEntity::LianaEntity(Coord position):
Entity(position) { }


void
LianaEntity::update(Map &map) {
    if (_isEmpty(map, Direction::UP)) {
        // Empty above, so destroy this liana block
        map.deleteEntity(position);
    }

    if (_isEmpty(map, Direction::DOWN)) {
        // Empty below, so grow downwards
        map.setEntity(std::make_unique<LianaEntity>(position + directionStep(Direction::DOWN)));
    }
}
