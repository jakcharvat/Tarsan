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
    if (window) {
        wattrset(window, Color::pair(COLOR_GREEN, COLOR_DEFAULT));
    }
    return '|';
}


LianaEntity::LianaEntity(Coord position):
Entity(std::move(position), RaycastLayer::LIANA) { }


void
LianaEntity::update(Map &map) {
    if (_isEmpty(map, Direction::UP)) {
        // Empty above, so destroy this liana block
        map.deleteEntity(position);
    }

    if (_isEmpty(map, Direction::DOWN)) {
        // Check for lava
        Coord below = position + directionStep(Direction::DOWN);
        if (!map.at(below) || !map.at(below)->isLava()) {
            // Empty below, so grow downwards
            map.setEntity(std::make_unique<LianaEntity>(below));
        }
    }
}
