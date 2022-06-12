//
//  fatal-error.hpp
//  Tarsan
//
//  Created by Jakub Charvát on 12.06.2022.
//

#pragma once

#include <exception>
#include <string>


///
/// A class representing an error shutting down the app
///
class FatalError: public std::exception {
private:
    ///
    /// The error message
    ///
    std::string _error;

public:
    /// Make the error
    /// @param message the error message
    FatalError(std::string message);

    const char * what() const noexcept override;
};
