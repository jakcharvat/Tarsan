//
//  map-generator-config.cpp
//  Tarsan
//
//  Created by Jakub Charvát on 12.06.2022.
//

#include "map-generator-config.hpp"

#include <fstream>

#include "file-parser.hpp"
#include "../logging/fatal-error.hpp"


MapGeneratorConfig
MapGeneratorConfig::loadFromFile(std::string filename) {
    MapGeneratorConfig config;

    std::ifstream file (filename);
    if (!file) return config;

    auto validateNumber = [&](const std::pair<std::string, int> & pair) {
        if (pair.second < 0 || pair.second > 100) {
            file.close();
            throw FatalError("Generator config file error: Invalid probability for key " + pair.first + ": " + std::to_string(pair.second));
        }
    };

    try {
        auto data = FileParser::parse(file);

        for (const auto & pair : data) {
            if (pair.first == "WIDTH") {
                config.mapWidth = pair.second;
            } else if (pair.first == "HEIGHT") {
                config.mapHeight = pair.second;
            } else if (pair.first == "STONE_PROB") {
                validateNumber(pair);
                config.stoneProbability = pair.second;
            } else if (pair.first == "LIANA_PROB") {
                validateNumber(pair);
                config.lianaProbability = pair.second;
            } else if (pair.first == "LAVA_PROB") {
                validateNumber(pair);
                config.lavaProbability = pair.second;
            } else {
                file.close();
                throw FatalError("Unknown generator config key: " + pair.first);
            }
        }
    } catch (const FileParser::ParseError &e) {
        file.close();
        throw FatalError("Couldn't parse generator config file: " + std::string { e.what() });
    }

    file.close();

    if (config.stoneProbability + config.lianaProbability + config.lavaProbability > 100) {
        throw FatalError("Generator config file error: Probabilities add up to more than 100");
    }

    return config;
}
