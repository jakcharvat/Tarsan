//
//  map-generator.cpp
//  Tarsan
//
//  Created by Jakub Charvát on 12.06.2022.
//

#include "map-generator.hpp"

#include "stone-entity.hpp"
#include "player-entity.hpp"
#include "liana-entity.hpp"
#include "lava-entity.hpp"
#include "map-generator-config.hpp"


MapGenerator::EntityMap
MapGenerator::getMap() const {
    MapGeneratorConfig config = MapGeneratorConfig::loadFromFile("examples/generator.config");
    
    const int WIDTH = config.mapWidth;
    const int HEIGHT = config.mapHeight;

    EntityMap map;
    for (int i = 0; i < HEIGHT; ++i) {
        EntityRow row;
        for (int j = 0; j < WIDTH; ++j) {
            std::unique_ptr<Entity> entity;
            Coord position { j, i };
            if (i == 0 || j == 0 || i == HEIGHT - 1 || j == WIDTH - 1) {
                entity = std::make_unique<StoneEntity>(position);
            } else {
                int num = random() % 100;
                if (num < config.stoneProbability) {
                    entity = std::make_unique<StoneEntity>(position);
                } else if (num < config.stoneProbability + config.lianaProbability) {
                    entity = std::make_unique<LianaEntity>(position);
                } else if (num < config.stoneProbability + config.lianaProbability + config.lavaProbability) {
                    entity = std::make_unique<LavaEntity>(position);
                }
            }

            row.push_back(std::move(entity));
        }
        map.push_back(std::move(row));
    }

    return map;
}
