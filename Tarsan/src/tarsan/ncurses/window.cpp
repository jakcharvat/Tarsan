//
//  window.cpp
//  Tarsan
//
//  Created by Jakub Charvát on 12.06.2022.
//

#include "window.hpp"

#include "../logging/pause-error.hpp"
#include "../logging/fatal-error.hpp"


Window::Window(WINDOW * parent, Coord origin, Coord size, bool border):
_parentWindow(parent) {
    PauseError sizeErr ("Window too small");
    FatalError windowErr ("Cannot create window");

    if (origin.x < 0 || origin.y < 0) throw sizeErr;

    int x, y;
    getmaxyx(stdscr, y, x);
    Coord opposite = origin + size;
    if (opposite.x > x || opposite.y > y) throw sizeErr;

    if (border) {
        if (origin.x < 1 || origin.y < 1) throw sizeErr;
        if (opposite.x + 1 > x || opposite.y + 1 > y) throw sizeErr;

        _borderWindow = newwin(size.y + 2, size.x + 2, origin.y - 1, origin.x - 1);
        if (!_borderWindow) throw windowErr;

        wclear(_borderWindow);
        box(_borderWindow, 0, 0);
        wrefresh(_borderWindow);
    }

    _contentWindow = newwin(size.y, size.x, origin.y, origin.x);
    if (!_contentWindow) throw windowErr;

    wclear(_contentWindow);
    wrefresh(_contentWindow);
}
