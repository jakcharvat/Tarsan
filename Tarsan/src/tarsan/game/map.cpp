//
//  map.cpp
//  Tarsan
//
//  Created by Jakub Charvát on 12.06.2022.
//

#include "map.hpp"


Map::EntityMap
Map::_generateRandomMap() {
    const int WIDTH = 20;
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
                int type = random() % 1;
                switch (type) {
                    case 0: {
                        entity = nullptr;
                        break;
                    }
                    case 1: {
                        entity = std::make_unique<StoneEntity>(position);
                        break;
                    }
                    case 2: {
                        entity = std::make_unique<LianaEntity>(position);
                        break;
                    }
                    case 3: {
                        entity = std::make_unique<LavaEntity>(position);
                        break;
                    }
                }
            }

            row.push_back(std::move(entity));
        }
        map.push_back(std::move(row));
    }


    for (int x = 1; x < 10; ++x) {
        map[9][x] = std::make_unique<StoneEntity>(Coord {x, 9});
    }

    map[10][1] = std::make_unique<LianaEntity>(Coord {1, 10});

    return map;
}


void
Map::draw(WINDOW *window) const {
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


int Map::raycast(Coord origin, RaycastDirection direction, int limit) const {
    const int step = direction == RaycastDirection::DOWN ? 1 : -1;
    int ray = 0;

    origin.y += step;
    while (_map[origin.y][origin.x] == nullptr) {
        if (limit != -1 && ray >= limit) break;

        ray += 1;
        origin.y += step;
    }

    return ray;
}
