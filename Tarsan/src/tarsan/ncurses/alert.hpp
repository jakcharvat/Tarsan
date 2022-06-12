//
//  alert.hpp
//  Tarsan
//
//  Created by Jakub Charvát on 12.06.2022.
//

#pragma once

#include <string>

#include "drawable.hpp"
#include "input-window.hpp"
#include "../helpers/coord.hpp"


///
/// A class wrapping a simple alert dialog
///
class Alert: public Drawable {
private:
    ///
    /// The main error message
    ///
    std::string _error;

    ///
    /// The subtext hint of the error message
    ///
    std::string _hint;

    /// Calculate the bounding box for a given string
    /// @param text the text to calculate for
    /// @param w the width of the window
    Coord _calculateBoundingBox(const std::string & text, int w) const;

public:
    /// Make an alert with the given string and hint
    /// @param error the main error message
    /// @param hint the hint subtext message
    Alert(std::string error, std::string hint);

    /// Wait for the user to press a button before closing this dialog
    /// @param input the input controller
    /// @return false if application quit was requested by the escape key, false otherwise
    bool waitForUserInteraction(InputWindow & input);

    void draw(WINDOW *window) override;
};
