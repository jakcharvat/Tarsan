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
    char getChar() const override;
};
