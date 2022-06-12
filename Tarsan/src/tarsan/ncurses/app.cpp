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
#include "../logging/menu-error.hpp"
#include "../logging/pause-error.hpp"
#include "../logging/out.hpp"
#include "../ncurses/char-helpers.hpp"


void
App::update() {
    int key;
    while ((key = _input->poll()) != -1) {
        _map->handleEvent(key);
    }
    _map->update();
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


void
App::run() {
    _nextPoll = std::chrono::steady_clock::now();
    _nextUpdate = std::chrono::steady_clock::now();

    try {
        _input->setup();
        _window->setup();
    } catch (const MenuError & e) {
        throw FatalError("Window setup error");
    } catch (const PauseError & e) {
        throw FatalError("Window setup error");
    }

    _window->draw();

    while (true) {
        int c = _input->getchar();
        _window->draw();

        out() << "Got char " << c << std::endl;

        if (CharHelpers::isEscape(c)) break;
//        if (c != -1) _input->buffer(c);
        if (c != -1) _map->handleEvent(c);

        if (_nextUpdate <= std::chrono::steady_clock::now()) {
            update();
            _nextUpdate = _nextUpdate + UPDTATE_DURATION;
        }

        auto nextPoll = _nextPoll + POLL_DURATION;
        _nextPoll = nextPoll;
        std::this_thread::sleep_until(nextPoll);
    }
}


App::~App() {
    curs_set(1);
    endwin();
}
