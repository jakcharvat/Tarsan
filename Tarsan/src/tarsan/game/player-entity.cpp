//
//  player-entity.cpp
//  Tarsan
//
//  Created by Jakub Charvát on 12.06.2022.
//

#include "player-entity.hpp"

#include "../ncurses/color.hpp"
#include "../logging/out.hpp"

#include "map.hpp"


void
PlayerEntity::_performFall(int distance) {
    position.y += distance;
    _vertVelocity = 0;

    //TODO: Take damage
    _tookDamage = true;
}


char
PlayerEntity::_getChar(WINDOW * window) const {
    const int colour = _tookDamage ? COLOR_RED : COLOR_GREEN;
    const int bold = _tookDamage ? A_BOLD | A_REVERSE : 0;
    wattrset(window, Color::pair(colour, COLOR_DEFAULT) | bold);
    return '>';
}


PlayerEntity::PlayerEntity(Coord position):
Entity(position) { }


void
PlayerEntity::update(Map &map) {
    _tookDamage = false;

    int free = map.raycast(position, Map::RaycastDirection::DOWN, std::max(0, _vertVelocity + 1));

    if (free > 0) {
        if (free > _vertVelocity) {
            position.y += _vertVelocity;
            _vertVelocity += 1;
        } else {
            _performFall(free);
        }
    }
}
