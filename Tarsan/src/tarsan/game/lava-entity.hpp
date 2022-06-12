//
//  lava-entity.hpp
//  Tarsan
//
//  Created by Jakub Charvát on 12.06.2022.
//

#pragma once

#include "entity.hpp"


///
/// A class representing a single block of lava
///
class LavaEntity: public Entity {
private:
    ///
    /// The level to be used for source lava entities
    /// 
    static constexpr short SOURCE_LAVA_LEVEL = 6;

    /// The fullness level of this lava block
    ///
    /// Scale is from 1 to 5 where one is very little lava and 5 is full lava. 6 represents a source block
    short _level = SOURCE_LAVA_LEVEL;

    /// Spread the lava to side if possible
    /// @param map the map to spread in
    /// @param direction the direction to spread in -- must be either left or right
    void _spreadToSide(Map & map, Direction direction);

    char _getChar(WINDOW * window) const override;

public:
    /// Construct a non source lava entity at the given position with the given level
    /// @param position the position to construct at
    /// @param level the level of this lava entity
    LavaEntity(Coord position, int level);

    /// Construct a source lava entity at the given position
    /// @param position the position to construct at
    LavaEntity(Coord position);

    short getLavaLevel() const override;
    void update(Map &map) override;
};
