//
//  test.cpp
//  Quizzy
//
//  Created by Jakub Charvát on 05.06.2022.
//

#ifdef __TEST__

#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>

#include "tarsan/game/file-parser.hpp"
#include "tarsan/game/map-generator-config.hpp"
#include "tarsan/logging/fatal-error.hpp"



std::unordered_map<std::string, int> testFile(std::string filename) {
    std::ifstream ifs (filename);
    return FileParser::parse(ifs);
}


int main () {
    try {
        auto data = testFile("examples/generator.config");
        assert(data["WIDTH"] == 20);
        assert(data["HEIGHT"] == 10);
        assert(data["STONE_PROB"] == 50);
    } catch (const FileParser::ParseError &) {
        assert(false);
    }

    try {
        testFile("examples/missingValue.txt");
        assert(false);
    } catch (const FileParser::ParseError &) { }

    try {
        testFile("examples/nonIntValue.txt");
        assert(false);
    } catch (const FileParser::ParseError &) { }

    try {
        testFile("examples/noSemicolon.txt");
        assert(false);
    } catch (const FileParser::ParseError &) { }

    try {
        testFile("examples/duplicateKey.txt");
        assert(false);
    } catch (const FileParser::ParseError &) { }


    try {
        MapGeneratorConfig config = MapGeneratorConfig::loadFromFile("examples/generator.config");
        assert(config.mapWidth == 20);
        assert(config.mapHeight == 10);
        assert(config.stoneProbability == 50);
        assert(config.lianaProbability == 15);
        assert(config.lavaProbability == 3);
    } catch (const FileParser::ParseError &) {
        assert(false);
    }


    try {
        MapGeneratorConfig::loadFromFile("examples/unknownKeyGenerator.config");
        assert(false);
    } catch (const FatalError &) { }


    try {
        MapGeneratorConfig::loadFromFile("examples/percentageOverflowGenerator.config");
        assert(false);
    } catch (const FatalError &) { }


    std::cout << "All tests passed :)" << std::endl;
}


#endif
