//
//  window.hpp
//  Tarsan
//
//  Created by Jakub Charvát on 12.06.2022.
//

#pragma once

#include <ncurses.h>

#include "../helpers/coord.hpp"


/// A class managing a single ncurses window instance
///
/// Almost. If the window is bordered then two nested windows are managed with one being larger to accomodate the border.
class Window {
private:
    /// The parent window to this window
    ///
    /// Used to restore it back when this window is hidden. Requirs that `_parentWindow` covers at least the full span of `_contentWindow` and `_borderWindow`, if set
    ///
    ///FIXME: Not used for now
    WINDOW * const _parentWindow = nullptr;
    ///
    /// The window managing the border
    ///
    WINDOW * _borderWindow = nullptr;

    ///
    /// The window managing the content
    ///
    WINDOW * _contentWindow = nullptr;


public:
    /// Create a window at the given coordinates
    ///
    /// The coordinates represent the origin of the content window. If a border is requested via `bordered`, then that spans past the origin.
    ///
    /// @param parent the parent window
    /// @param origin the origin of the content window
    /// @param size the size of the content window
    /// @param border whether the window should draw a border
    Window(WINDOW * parent, Coord origin, Coord size, bool border);
};
