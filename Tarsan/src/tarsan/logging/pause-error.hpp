//
//  pause-error.hpp
//  Tarsan
//
//  Created by Jakub Charvát on 12.06.2022.
//

#pragma once

#include <exception>
#include <string>


/// The least severe type of error
///
/// Allows the user to continue where they left of as soon as the error is fixed
class PauseError: public std::exception {
    ///
    /// The error message
    ///
    std::string _error;

public:
    /// Make the error
    /// @param message the error message
    PauseError(std::string message);

    const char * what() const noexcept override;
};
