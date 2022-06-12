//
//  map.hpp
//  Tarsan
//
//  Created by Jakub Charvát on 12.06.2022.
//

#pragma once

#include <memory>
#include <vector>

#include "entity.hpp"
#include "stone-entity.hpp"
#include "player-entity.hpp"
#include "liana-entity.hpp"
#include "lava-entity.hpp"


class Map {
private:
    using EntityPtr = std::unique_ptr<Entity>;
    using EntityRow = std::vector<EntityPtr>;
    using EntityMap = std::vector<EntityRow>;

    ///
    /// Generate a random map
    ///
    static EntityMap _generateRandomMap();

    ///
    /// A vector storing the full map
    ///
    EntityMap _map = _generateRandomMap();

public:
    /// Draw the map to the given window
    /// @param window the window to draw to
    void draw(WINDOW * window) const;
};
