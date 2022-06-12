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
    static constexpr std::chrono::milliseconds POLL_DURATION { 100 };

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
    /// The map of the current game
    ///
    std::unique_ptr<Map> _map = std::make_unique<Map>();

    ///
    /// Update the game
    ///
    void update();

    ///
    /// A queue of characters received since the last update
    std::queue<int> chars;


public:
    ///
    /// Setup ncurses
    ///
    App();


    ///
    /// Start actually running the app
    ///
    void run();


    ///
    /// Cleanup ncurses
    ///
    ~App();
};
