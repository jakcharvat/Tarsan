//
//  map-generator.hpp
//  Tarsan
//
//  Created by Jakub Charvát on 12.06.2022.
//

#pragma once

#include "map-loader.hpp"


class MapGenerator: public MapLoader {
    EntityMap getMap() override;
};
