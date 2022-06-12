//
//  input-window.hpp
//  Tarsan
//
//  Created by Jakub Charvát on 12.06.2022.
//

#pragma once

#include "window.hpp"

#include <queue>


/// A window that listens for user input
///
/// This is handled in a separate window to avoid ncurses window refreshes on getch() calls
class InputWindow: private Window {
    ///
    /// The keys waiting to be processed by the game
    ///
    std::queue<int> _buffer;

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

    /// Block the thread until a key is received
    /// @returns the key received
    int blockingGetchar();

    /// Store a character to be available during the next update
    /// @param c the char to store
    void buffer(int c);

    /// Pull the first character waiting for a game update
    /// @returns the first element in the queue
    int poll();
};
