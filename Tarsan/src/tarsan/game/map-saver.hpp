//
//  map-saver.hpp
//  Tarsan
//
//  Created by Jakub Charvát on 12.06.2022.
//

#pragma once

#include <memory>
#include <vector>

#include "entity.hpp"
#include "player-entity.hpp"
#include "savable.hpp"

std::string currentDateAndTime();


///
/// A struct facilitating saving a game state
///
struct MapSaver {
    static void save (const Savable & savable);
};
