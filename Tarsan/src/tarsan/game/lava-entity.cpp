//
//  lava-entity.cpp
//  Tarsan
//
//  Created by Jakub Charvát on 12.06.2022.
//

#include "lava-entity.hpp"

#include "../ncurses/color.hpp"

#include "map.hpp"


LavaEntity::LavaEntity(Coord position, int level):
Entity(std::move(position), RaycastLayer::LAVA),
_level(level) { }


void
LavaEntity::_spreadToSide(Map &map, Direction direction) {
    if (direction != Direction::LEFT && direction != Direction::RIGHT) return;
    if (_level <= 1) return;

    bool isEmpty = map.raycast(position, direction, dangerRaycastMask(RaycastLayer::LAVA));
    if (isEmpty) {
        Coord stepCoord = position + directionStep(direction);
        map.setEntity(std::make_unique<LavaEntity>(stepCoord, _level - 1));
    }
}


char
LavaEntity::_getChar(WINDOW * window) const {
    wattrset(window, Color::pair(COLOR_RED, COLOR_DEFAULT));
//    return '#';
    return _level + '0';
};


LavaEntity::LavaEntity(Coord position):
Entity(std::move(position), RaycastLayer::LAVA) { }


short
LavaEntity::getLavaLevel() const {
    return _level;
}


void
LavaEntity::update(Map &map) {
    const auto coords = {
        position + directionStep(Direction::UP),
        position + directionStep(Direction::LEFT),
        position + directionStep(Direction::RIGHT),
    };

    int maxLevel = 0;
    for (auto coord : coords) {
        const Entity * ent = map.at(coord);
        if (ent && ent->getLavaLevel() >= maxLevel) {
            maxLevel = ent->getLavaLevel();
        }
    }

    bool remove = maxLevel < _level;
    if (remove && _level < SOURCE_LAVA_LEVEL) map.deleteEntity(position);

    if (maxLevel - 1 > _level) {
        _level = maxLevel - 1;
    }

    if (_isOnGround(map)) {
        _spreadToSide(map, Direction::LEFT);
        _spreadToSide(map, Direction::RIGHT);
    } else {
        Coord below = position + directionStep(Direction::DOWN);
        map.setEntity(std::make_unique<LavaEntity>(below, _level));
    }
}
