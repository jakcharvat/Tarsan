//
//  map.hpp
//  Tarsan
//
//  Created by Jakub Charvát on 12.06.2022.
//

#pragma once

#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "../ncurses/drawable.hpp"

#include "entity.hpp"
#include "stone-entity.hpp"
#include "player-entity.hpp"
#include "liana-entity.hpp"
#include "lava-entity.hpp"


class Map: public Drawable {
public:
    using EntityPtr = std::unique_ptr<Entity>;
    using EntityRow = std::vector<EntityPtr>;
    using EntityMap = std::vector<EntityRow>;

private:
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

    ///
    /// A set of the positions of entities that should be deleted before the next render pass
    ///
    std::unordered_set<Coord> _toDelete;

    ///
    /// A map of entities that should be inserted before the next render pass
    ///
    std::unordered_map<Coord, EntityPtr> _toInsert;

    ///
    /// Delete all entities in the `_toDelete` queue
    ///
    void _deleteAllPending();

    ///
    /// Insert all entities waiting for insertion
    ///
    void _insertAllPending();

    /// Check whether the entity at the specified position is modifiable
    ///
    /// All entities are modifiable except border entities
    /// @param position the position to check
    /// @return true if the entity is modifiable
    bool _isModifiable(Coord position) const;

public:
    /// Draw the map to the given window
    /// @param window the window to draw to
    void draw(WINDOW * window);

    ///
    /// Perform a single frame update
    /// 
    void update();

    /// Fire a raycast in the specified direction
    /// @param origin the point to fire from
    /// @param direction the direction to fire in
    /// @param mask the layers to include in the search
    /// @param limit the maximum number of steps. -1 for an unlimited ray
    /// @returns the number of free blocks (not stones) in the direction of the raycast
    int raycast(Coord origin, Direction direction, int mask = dangerRaycastMask(RaycastLayer::STONE), int limit = -1) const;

    /// Register an entity for deletion in the next render pass
    /// @param coordinate the coordinate of the entity that should be deleted
    void deleteEntity(Coord coordinate);

    /// Set the specified entity at the given coordinate
    /// @param pointer a pointer to the new entity
    void setEntity(EntityPtr pointer);

    /// Get the entity at a specified position
    /// @param coord the position to look at
    /// @returns a pointer to a constant entity
    const Entity * at(Coord coord) const;

    /// Handle a registered key event
    /// @param key the key corresponding to the event
    void handleEvent(int key);

    /// Get the size of the map
    /// @returns the size of the map
    Coord size() const;
};
