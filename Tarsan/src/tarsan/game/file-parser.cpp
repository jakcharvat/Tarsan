//
//  file-parser.cpp
//  Tarsan
//
//  Created by Jakub Charvát on 12.06.2022.
//

#include "file-parser.hpp"



std::unordered_map<std::string, int>
FileParser::parse(std::ifstream &stream) {
    std::unordered_map<std::string, int> data;

    while (stream) {
        std::string key;
        stream >> key;
        if (!stream) break;

        if (key.front() == '#') {
            char c = 0;
            while (stream && c != '\n') {
                stream.get(c);
            }
            continue;
        }

        int value;
        stream >> value;
        if (!stream) throw ParseError("Couldn't parse value for key " + key);

        char c;
        stream >> c;
        if (!stream || c != ';') throw ParseError("Expected ';' after " + key + ": " + std::to_string(value));

        data[key] = value;
    }

    return data;
}


FileParser::ParseError::ParseError(std::string message):
_description(std::move(message)) { }


const char *
FileParser::ParseError::what() const noexcept {
    return _description.c_str();
}
