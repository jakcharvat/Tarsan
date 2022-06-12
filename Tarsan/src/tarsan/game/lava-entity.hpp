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
    char _getChar(WINDOW * window) const override;

public:
    /// Construct a lava entity at the given position
    /// @param position the position to construct at
    LavaEntity(Coord position);
};
