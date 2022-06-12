//
//  player-entity.hpp
//  Tarsan
//
//  Created by Jakub Charvát on 12.06.2022.
//

#include "entity.hpp"


///
/// A class storing a player entity
/// 
class PlayerEntity: public Entity {
    char getChar(WINDOW * window) const override;

public:
    /// Construct a player entity at the given position
    /// @param position the position to construct at
    PlayerEntity(Coord position);
};
