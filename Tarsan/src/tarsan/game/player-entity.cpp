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


void
PlayerEntity::_move(Direction direction, Map &map) {
    if (!_isOnGround(map) && !_jumping && !_isOnLiana(map)) return;

    if (direction == Direction::LEFT || direction == Direction::RIGHT) {
        PlayerDirection pdir = direction == Direction::LEFT ? PlayerDirection::LEFT : PlayerDirection::RIGHT;
        _direction = pdir;
    }

    if (_isEmpty(map, direction)) {
        position = position + directionStep(direction);
    }
}


void
PlayerEntity::_jump(Map &map) {
    if (!_isOnGround(map) && !_isOnLiana(map)) return;

    if (_isEmpty(map, Direction::UP)) {
        position = position + directionStep(Direction::UP);
        _jumping = true;
    }
}


bool
PlayerEntity::_isOnLiana(Map &map) {
    int mask = raycastMask(RaycastLayer::LIANA);
    Coord above = position + directionStep(Direction::UP);
    return map.raycast(above, Direction::DOWN, mask, 1) == 0;
}


char
PlayerEntity::_getChar(WINDOW * window) const {
    const int colour = _tookDamage ? COLOR_RED : COLOR_GREEN;
    const int bold = A_BOLD | A_REVERSE;
    wattrset(window, Color::pair(colour, COLOR_DEFAULT) | bold);
    return _direction == PlayerDirection::RIGHT ? '>' : '<';
}


PlayerEntity::PlayerEntity(Coord position):
Entity(std::move(position), RaycastLayer::EMPTY) { }


void
PlayerEntity::handleEvent(int key, Map &map) {
    if (key == KEY_LEFT) {
        _move(Direction::LEFT, map);
    } else if (key == KEY_RIGHT) {
        _move(Direction::RIGHT, map);
    } else if (key == KEY_UP) {
        _jump(map);
    } else if (key == KEY_DOWN) {
        _move(Direction::DOWN, map);
    }
}


void
PlayerEntity::update(Map &map) {
    _tookDamage = false;

    int free = map.raycast(position, Direction::DOWN, dangerRaycastMask(RaycastLayer::STONE), std::max(0, _vertVelocity + 1));

    if (_vertVelocity > 0) _jumping = false;

    if (free > 0 && !_isOnLiana(map)) {
        if (free > _vertVelocity) {
            position.y += _vertVelocity;
            _vertVelocity += 1;
        } else {
            _performFall(free);
//            map.deleteEntity(position + Coord { 0, 2 });
        }
    }
}
