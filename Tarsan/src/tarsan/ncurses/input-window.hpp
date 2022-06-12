//
//  input-window.hpp
//  Tarsan
//
//  Created by Jakub Charvát on 12.06.2022.
//

#pragma once

#include "window.hpp"


/// A window that listens for user input
///
/// This is handled in a separate window to avoid ncurses window refreshes on getch() calls
class InputWindow: private Window {
public:
    ///
    /// Create an empty window
    ///
    InputWindow();

    /// Set this window up to receive events
    /// @throws if the setup is unsuccessful
    void setup();

    /// Get a character
    /// @returns a character received from ncurses
    int getchar();
};
