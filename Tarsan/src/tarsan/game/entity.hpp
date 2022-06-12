//
//  entity.hpp
//  Tarsan
//
//  Created by Jakub Charvát on 12.06.2022.
//

#pragma once

#include <ncurses.h>

#include "../helpers/direction.hpp"
#include "../helpers/raycast-layer.hpp"


class Map;


///
/// A class storing a single entity
///
class Entity {
private:
    /// Get the char to represent this entity.
    ///
    /// If needed, this method can also set a specific style for the entity
    ///
    /// @param window the window to use for drawing. Can be used to set attributes on it
    /// @returns the char to draw
    virtual char _getChar(WINDOW *window) const = 0;

protected:
    /// Check if the neighbouring block in the specified direction is empty
    /// @param map the map to use for the check
    /// @param direction the direction to look in
    /// @returns true is the block is empty
    bool _isEmpty(Map &map, Direction direction) const;

    /// Check if the entity is standing on the ground
    /// @param map the map to use for the check
    /// @returns true if the entity is on the ground
    bool _isOnGround(Map &map) const;

public:
    ///
    /// The current position of the entity
    ///
    Coord position;

    ///
    /// The raycast layer of this entity
    ///
    const RaycastLayer raycastLayer;

    /// Construct an entity at the given position
    /// @param position the position to construct at
    /// @param raycastLayer the raycast layer of this entity
    Entity(Coord position, RaycastLayer raycastLayer);

    /// Performa a single frame update of this entity
    ///
    /// @param map a reference to the map so the entity can move itself if needed
    virtual void update(Map &map);
    
    /// Draw this entity to the given window
    /// @param window the window to draw to
    void draw(WINDOW * window) const;

    /// Check whether this entity is a lava entity
    /// @returns true if this is a lava entity
    bool isLava() const;

    /// Check the lava level at this entity
    /// @returns the lava level of this entity, 0 if there is no lava
    virtual short getLavaLevel() const;

    ///
    /// Virtual destructor for abstract class
    /// 
    virtual ~Entity() = default;
};
