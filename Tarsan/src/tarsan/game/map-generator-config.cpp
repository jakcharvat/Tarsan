//
//  map-generator-config.cpp
//  Tarsan
//
//  Created by Jakub Charvát on 12.06.2022.
//

#include "map-generator-config.hpp"

#include <fstream>


MapGeneratorConfig
MapGeneratorConfig::loadFromFile(std::string filename) {
    MapGeneratorConfig config;

    std::ifstream file (filename);
    if (!file) return config;

    file.close();

    return config;
}
