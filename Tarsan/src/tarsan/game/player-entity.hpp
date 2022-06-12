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
    char getChar() const override;
};
