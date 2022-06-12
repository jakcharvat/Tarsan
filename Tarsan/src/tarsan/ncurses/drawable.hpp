//
//  drawable.hpp
//  Tarsan
//
//  Created by Jakub Charvát on 12.06.2022.
//

#pragma once

#include <ncurses.h>


///
/// A class representing a single drawable object
/// 
class Drawable {
public:
    /// Draw the element to the given ncurses window.
    /// @param window the window to draw to
    virtual void draw(WINDOW * window) = 0;

    ///
    /// Virtual destructor needed for base class
    ///
    virtual ~Drawable() = default;
};
