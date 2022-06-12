//
//  app.cpp
//  Tarsan
//
//  Created by Jakub Charvát on 12.06.2022.
//

#include "app.hpp"

#include <clocale>
#include <fcntl.h>
#include <thread>
#include <unistd.h>
#include <iostream>


#include "../logging/fatal-error.hpp"
#include "../logging/pause-error.hpp"
#include "../logging/out.hpp"
#include "../ncurses/alert.hpp"
#include "../ncurses/char-helpers.hpp"


void
App::_update() {
    _map->update();
}


bool
App::_showAlert(const MenuError &err) {
    std::shared_ptr<Alert> alert (new Alert (err.what(), "Press any key to start a new game"));

    int w, h;
    getmaxyx(stdscr, h, w);
    Window window (stdscr, alert, { 1, 1 }, { w - 2, h - 2 });
    window.setup();
    window.draw();
    return alert->waitForUserInteraction(*_input);
}


App::App() {
    set_escdelay(20);
    // Setup inspired by
    // https://linuxjedi.co.uk/2020/04/29/event-loops-and-ncurses/amp/
    setlocale(LC_ALL, "");
    if (!initscr()) {
        throw FatalError("Cannot init ncurses window");
    }

    noecho();

    int width, height;
    getmaxyx(stdscr, height, width);

    if (width < MIN_WIDTH || height < MIN_HEIGHT) {
        curs_set(1);
        endwin();
        throw FatalError("Screen to small");
    }

    if (use_default_colors() == ERR || start_color() == ERR) {
        curs_set(1);
        endwin();
        throw FatalError("Terminal doesn't support colour output");
    }

    curs_set(0);
}


bool
App::run(const MapLoader & loader) {
    _map = std::make_shared<Map>(loader.getMap());

    _nextPoll = std::chrono::steady_clock::now();
    _nextUpdate = std::chrono::steady_clock::now();

    try {
        _input->setup();

        Coord available { 0, 0 }; getmaxyx(stdscr, available.y, available.x);
        Coord mapSize = _map->size();

        int paddingLeft = (available.x - mapSize.x) / 2;
        int paddingTop = (available.y - mapSize.y) / 2;


        _window = std::make_unique<Window>(stdscr, _map, Coord { paddingLeft, paddingTop }, mapSize);
        _window->setup();
    } catch (const MenuError & e) {
        throw FatalError("Window setup error");
    } catch (const PauseError & e) {
        throw FatalError("Window setup error");
    }

    try {
        while (true) {
            int c = _input->getchar();
            _window->draw();

            out() << "Got char " << c << std::endl;

            if (CharHelpers::isEscape(c)) return false;
            if (c != -1) _map->handleEvent(c);
            if (c == 'r') break;

            if (_nextUpdate <= std::chrono::steady_clock::now()) {
                _update();
                _nextUpdate = _nextUpdate + UPDTATE_DURATION;
            }

            auto nextPoll = _nextPoll + POLL_DURATION;
            _nextPoll = nextPoll;
            std::this_thread::sleep_until(nextPoll);
        }
    } catch (const MenuError & e) {
        return _showAlert(e);
    }

    return true;
}


App::~App() {
    curs_set(1);
    endwin();
}
