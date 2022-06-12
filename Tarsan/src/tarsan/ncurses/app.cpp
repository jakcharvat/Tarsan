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
#include "../logging/out.hpp"


void
App::update() {

}


App::App() {
    // Setup inspired by
    // https://linuxjedi.co.uk/2020/04/29/event-loops-and-ncurses/amp/
    setlocale(LC_ALL, "");
    if (!initscr()) {
        throw FatalError("Cannot init ncurses window");
    }

    keypad(stdscr, true);
    noecho();

    // Make sure non-blocking mode is set on the keyboard
    int val = fcntl(STDIN_FILENO, F_GETFL, 0);
    if (val != -1) {
        fcntl(STDIN_FILENO, F_SETFL, val | O_NONBLOCK);
    }

    int width, height;
    getmaxyx(stdscr, height, width);

    if (width < MIN_WIDTH || height < MIN_HEIGHT) {
        curs_set(1);
        endwin();
        throw FatalError("Screen to small");
    }
}


void
App::run() {
    int i = 0;
    _nextPoll = std::chrono::steady_clock::now();
    _nextUpdate = std::chrono::steady_clock::now();

    while (true) {
        mvprintw(1, 1, "%d", i++);
        refresh();

        int c = getch();
        out() << c << std::endl;

        if (c == 'q') break;

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
