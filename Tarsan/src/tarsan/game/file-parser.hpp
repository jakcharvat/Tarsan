//
//  file-parser.hpp
//  Tarsan
//
//  Created by Jakub Charvát on 12.06.2022.
//

#pragma once

#include <fstream>
#include <string>
#include <unordered_map>


///
/// A structure to abstract parsing config files
///
struct FileParser {
    /// Parse the given stream into a dictionary of key-value pairs with integer values
    /// @param stream the stream to parse from
    /// @returns a map container storing the data from the file
    static std::unordered_map<std::string, int> parse (std::ifstream & stream);


    ///
    /// A file parse error
    ///
    class ParseError: public std::exception {
        ///
        /// A description of the error
        ///
        const std::string _description;

    public:
        /// Make the error
        /// @param message the error message
        ParseError(std::string message);

        const char * what() const noexcept override;
    };
};
