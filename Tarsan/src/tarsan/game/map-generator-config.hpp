//
//  map-generator-config.hpp
//  Tarsan
//
//  Created by Jakub Charvát on 12.06.2022.
//

#pragma once

#include <string>


struct MapGeneratorConfig {
    ///
    /// The width of the map
    ///
    int mapWidth = 40;

    ///
    /// The height of the map
    ///
    int mapHeight = 20;

    ///
    /// The probability of generating a stone. Out of 100
    ///
    int stoneProbability = 25;

    ///
    /// The probability of generating a liana. Out of 100
    ///
    int lianaProbability = 15;

    ///
    /// The probability of generating a lava source. Out of 100
    ///
    int lavaProbability = 3;

    /// Load a config from a file
    /// @param filename the file to load from
    /// @returns a config structure
    static MapGeneratorConfig loadFromFile (std::string filename);
};
