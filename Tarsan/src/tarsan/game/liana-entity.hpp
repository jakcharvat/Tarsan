//
//  liana-entity.hpp
//  Tarsan
//
//  Created by Jakub Charvát on 12.06.2022.
//

#pragma once

#include "entity.hpp"


///
/// A class storing a liana entity
///
class LianaEntity: public Entity {
    char getChar() const override;

public:
    /// Construct a liana entity at the given position
    /// @param position the position to construct at
    LianaEntity(Coord position);
};
