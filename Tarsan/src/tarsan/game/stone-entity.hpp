//
//  stone-entity.hpp
//  Tarsan
//
//  Created by Jakub Charvát on 12.06.2022.
//

#pragma once

#include "entity.hpp"


///
/// A class storing a stone entity
/// 
class StoneEntity: public Entity {
private:
    char _getChar(WINDOW * window) const override;

public:
    /// Construct a stone entity at the given position
    /// @param position the position to construct at
    StoneEntity(Coord position);
};
