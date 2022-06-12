//
//  app.hpp
//  Tarsan
//
//  Created by Jakub Charvát on 12.06.2022.
//

#pragma once

#include <chrono>
#include <ncurses.h>
#include <queue>

#include "../game/map.hpp"
#include "../logging/menu-error.hpp"

#include "input-window.hpp"
#include "window.hpp"


///
/// The main driver of the app
class App {
private:
    ///
    /// Minimum supported screen width
    ///
    static constexpr int MIN_WIDTH = 20;

    ///
    /// Minimum supported screen height
    ///
    static constexpr int MIN_HEIGHT = 20;

    ///
    /// The duration between key polls
    ///
    static constexpr std::chrono::milliseconds POLL_DURATION { 50 };

    ///
    /// The duration between game updates
    ///
    static constexpr std::chrono::milliseconds UPDTATE_DURATION { 500 };

    ///
    /// The time of next poll
    ///
    std::chrono::steady_clock::time_point _nextPoll;

    ///
    /// The time of next update
    ///
    std::chrono::steady_clock::time_point _nextUpdate;

    ///
    /// Input receiver
    ///
    std::unique_ptr<InputWindow> _input = std::make_unique<InputWindow>();

    ///
    /// The map of the current game
    ///
    std::shared_ptr<Map> _map = std::make_shared<Map>();

    ///
    /// The window of the current game
    ///
    std::unique_ptr<Window> _window = nullptr;

    ///
    /// Update the game
    ///
    void _update();

    /// Show an error message
    /// @param err the error to show the message for
    /// @returns whether a new game should start
    bool _showAlert(const MenuError & err);

    ///
    /// A queue of characters received since the last update
    std::queue<int> chars;


public:
    ///
    /// Setup ncurses
    ///
    App();


    /// Start actually running the app
    /// @returns true if another game should be started
    bool run();


    ///
    /// Cleanup ncurses
    ///
    ~App();
};
