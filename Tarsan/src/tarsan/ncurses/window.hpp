//
//  window.hpp
//  Tarsan
//
//  Created by Jakub Charvát on 12.06.2022.
//

#pragma once

#include <memory>
#include <ncurses.h>

#include "../helpers/coord.hpp"

#include "drawable.hpp"


/// A class managing a single ncurses window instance
///
/// Almost. If the window is bordered then two nested windows are managed with one being larger to accomodate the border.
class Window {
protected:
    /// The parent window to this window
    ///
    /// Used to restore it back when this window is hidden. Requirs that `_parentWindow` covers at least the full span of `_contentWindow` and `_borderWindow`, if set
    ///
    ///FIXME: Not used for now
    WINDOW * const _parentWindow = nullptr;

    ///
    /// The origin of this window
    ///
    const Coord _origin;

    ///
    /// The size of this window
    ///
    const Coord _size;

    ///
    /// Whether this window should be bordered
    ///
    const bool _bordered;

    ///
    /// The window managing the border
    ///
    WINDOW * _borderWindow = nullptr;

    ///
    /// The window managing the content
    ///
    WINDOW * _contentWindow = nullptr;

    ///
    /// The content of this window
    ///
    const std::shared_ptr<Drawable> _drawable;


public:
    /// Create a window at the given coordinates
    ///
    /// The coordinates represent the origin of the content window. If a border is requested via `bordered`, then that spans past the origin.
    ///
    /// @param parent the parent window
    /// @param drawable the content of this window
    /// @param origin the origin of the content window
    /// @param size the size of the content window
    /// @param border whether the window should draw a border
    Window(WINDOW * parent, std::shared_ptr<Drawable> drawable, Coord origin, Coord size, bool border = true);

    /// Whether or not this window has been set up
    /// @returns true if the window was set up
    bool isSetup() const;

    /// Setup this window.
    ///
    /// Create the child windows and ensure the window fits on screen
    /// @throws if the window couln't be set up
    void setup();

    ///
    /// Draw the window to the screen
    ///
    void draw() const;

    ///
    /// Cleanup
    ///
    ~Window();
};
