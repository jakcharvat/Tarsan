//
//  map.hpp
//  Tarsan
//
//  Created by Jakub Charvát on 12.06.2022.
//

#pragma once

#include <memory>
#include <vector>

#include "../ncurses/drawable.hpp"

#include "entity.hpp"
#include "stone-entity.hpp"
#include "player-entity.hpp"
#include "liana-entity.hpp"
#include "lava-entity.hpp"


class Map: public Drawable {
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

    ///
    /// The player
    ///
    PlayerEntity _player {{ 1, 1 }};

public:
    /// Draw the map to the given window
    /// @param window the window to draw to
    void draw(WINDOW * window) const;

    ///
    /// Perform a single frame update
    /// 
    void update();

    ///
    /// A direction a raycast can travel
    ///
    enum class RaycastDirection {
        UP, DOWN
    };

    /// Fire a raycast in the specified direction
    /// @param origin the point to fire from
    /// @param direction the direction to fire in
    /// @param limit the maximum number of steps. -1 for an unlimited ray
    /// @returns the number of free blocks (not stones) in the direction of the raycast
    int raycast(Coord origin, RaycastDirection direction, int limit) const;
};
