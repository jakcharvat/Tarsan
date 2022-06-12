//
//  map.cpp
//  Tarsan
//
//  Created by Jakub Charvát on 12.06.2022.
//

#include "map.hpp"

#include "../ncurses/color.hpp"


Map::EntityMap
Map::_generateRandomMap() {
    const int WIDTH = 40;
    const int HEIGHT = 20;

    EntityMap map;
    for (int i = 0; i < HEIGHT; ++i) {
        EntityRow row;
        for (int j = 0; j < WIDTH; ++j) {
            std::unique_ptr<Entity> entity;
            Coord position { j, i };
            if (i == 0 || j == 0 || i == HEIGHT - 1 || j == WIDTH - 1) {
                entity = std::make_unique<StoneEntity>(position);
            } else {
                if (random() % 4 == 0) {
                    entity = std::make_unique<StoneEntity>(position);
                } else if (random() % 4 == 0) {
                    entity = std::make_unique<LianaEntity>(position);
                } else if (random() % 50 == 0) {
                    entity = std::make_unique<LavaEntity>(position);
                }
            }

            row.push_back(std::move(entity));
        }
        map.push_back(std::move(row));
    }

//    map[1][18] = std::make_unique<LavaEntity>(Coord {18, 1});
//    map[18][13] = std::make_unique<LavaEntity>(Coord {13, 18});

//    map[2][1] = std::make_unique<LavaEntity>(Coord {1, 2});
//    map[1][2] = std::make_unique<LavaEntity>(Coord {2, 1});

//    for (int x = 1; x < 10; ++x) {
//        map[9][x] = std::make_unique<StoneEntity>(Coord {x, 9});
//    }
//
//    map[10][1] = std::make_unique<LianaEntity>(Coord {1, 10});

    return map;
}


void
Map::_deleteAllPending() {
    for (auto coord : _toDelete) {
        _map[coord.y][coord.x] = nullptr;
    }

    _toDelete.clear();
}


void
Map::_insertAllPending() {
    for (auto & el : _toInsert) {
        Coord coord = el.first;

        const EntityPtr & curr = _map[coord.y][coord.x];
        if (curr) {
            if (curr->raycastLayer <= el.second->raycastLayer) continue;
        }

        _map[coord.y][coord.x] = std::move(el.second);
    }

    _toInsert.clear();
}


bool
Map::_isModifiable(Coord position) const {
    if (position.x < 1 || position.y < 1) return false;
    if (static_cast<size_t>(position.y) >= _map.size() - 1) return false;
    if (static_cast<size_t>(position.x) >= _map[position.y].size() - 1) return false;
    return true;
}


void
Map::draw(WINDOW *window) {
    _deleteAllPending();
    _insertAllPending();

    for (size_t i = 0; i < _map.size(); ++i) {
        const EntityRow & row = _map[i];
        wmove(window, static_cast<int>(i), 0);

        for (size_t j = 0; j < row.size(); ++j) {
            const EntityPtr & entity = row[j];

            if (!entity) {
                wprintw(window, " ");
                continue;
            }

            entity->draw(window);
        }
    }

    _player.draw(window);

    int hp = _player.getHp();
    int lostHp = PlayerEntity::MAX_HP - hp;
    int width = size().x;
    int lostWidth = width * lostHp / PlayerEntity::MAX_HP;
    int barWidth = width - lostWidth;

    wmove(window, size().y - 1, 0);
    wattrset(window, Color::pair(COLOR_RED, COLOR_RED));
    wprintw(window, "%*s", barWidth, "");
    wattrset(window, Color::pair(COLOR_DEFAULT, COLOR_DEFAULT));
    wprintw(window, "%*s", lostWidth, "");
}


void
Map::update() {
    for (auto & row : _map) {
        for (auto & entity : row) {
            if (entity) entity->update(*this);
        }
    }

    _player.update(*this);
}


int Map::raycast(Coord origin, Direction direction, int mask, int limit) const {
    const Coord step = directionStep(direction);
    int ray = 0;

    origin = origin + step;
    while (_isModifiable(origin)) {
        if (limit != -1 && ray >= limit) break;

        const EntityPtr & ent = _map[origin.y][origin.x];
        RaycastLayer layer = ent ? ent->raycastLayer : RaycastLayer::EMPTY;
        if (raycastMaskMatches(mask, layer)) break;

        ray += 1;
        origin = origin + step;
    }

    return ray;
}


void
Map::deleteEntity(Coord coordinate) {
    if (!_isModifiable(coordinate)) return;
    _toDelete.insert(coordinate);
}


void
Map::setEntity(EntityPtr pointer) {
    if (!pointer) return;
    Coord coord = pointer->position;
    if (!_isModifiable(coord)) return;

    if (_toInsert.count(coord)) {
        if (_toInsert.at(coord)->raycastLayer <= pointer->raycastLayer) return;
    }
    _toInsert[coord] = std::move(pointer);
}


const Entity *
Map::at(Coord coord) const {
    return _map[coord.y][coord.x].get();
}


void
Map::handleEvent(int key) {
    _player.handleEvent(key, *this);
}


Coord
Map::size() const {
    if (_map.empty()) return { 0, 0 };

    return {
        static_cast<int>(_map[0].size()),
        static_cast<int>(_map.size() + 1),
    };
}
