//
//  entity.hpp
//  Tarsan
//
//  Created by Jakub Charvát on 12.06.2022.
//

#pragma once

#include <ncurses.h>

#include "../helpers/coord.hpp"


///
/// A class storing a single entity
///
class Entity {
private:
    /// Get the char to represent this entity.
    ///
    /// If needed, this method can also set a specific style for the entity
    ///
    /// @returns the char to draw
    virtual char getChar() const = 0;

public:
    /// Construct an entity at the given position
    /// @param position the position to construct at
    Entity(Coord position);
    
    /// Draw this entity to the given window
    /// @param window the window to draw to
    void draw (WINDOW * window) const;

    ///
    /// The current position of the entity
    ///
    Coord coord;

    ///
    /// Virtual destructor for abstract class
    /// 
    virtual ~Entity() = default;
};
