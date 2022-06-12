//
//  map-generator.hpp
//  Tarsan
//
//  Created by Jakub Charvát on 12.06.2022.
//

#pragma once

#include "map-loader.hpp"


///
/// A class that implements random generation of a map from a specific config.
///
class MapGenerator: public MapLoader {
    EntityMap getMap() const override;
};
