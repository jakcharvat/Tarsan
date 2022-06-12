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
    char getChar() const override;
};
