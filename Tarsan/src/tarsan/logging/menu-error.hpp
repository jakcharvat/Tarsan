//
//  menu-error.hpp
//  Tarsan
//
//  Created by Jakub Charvát on 12.06.2022.
//

#pragma once

#include <exception>
#include <string>


/// A less severe error than `FatalError`
///
/// This error doesn't force the app to shutdown, it merely forces it back into the menu with an error message
class MenuError: std::exception {
    ///
    /// The error message
    ///
    std::string _error;

public:
    /// Make the error
    /// @param message the error message
    MenuError(std::string message);

    const char * what() const noexcept override;
};
