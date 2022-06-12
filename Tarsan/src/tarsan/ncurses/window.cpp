//
//  window.cpp
//  Tarsan
//
//  Created by Jakub Charvát on 12.06.2022.
//

#include "window.hpp"

#include "../logging/pause-error.hpp"
#include "../logging/fatal-error.hpp"


Window::Window(WINDOW * parent, std::shared_ptr<Drawable> drawable, Coord origin, Coord size, bool border):
_parentWindow(parent),
_origin(origin),
_size(size),
_bordered(border),
_drawable(drawable) { }


bool
Window::isSetup() const {
    return _contentWindow != nullptr;
}


void
Window::setup() {
    PauseError sizeErr ("Window too small");
    FatalError windowErr ("Cannot create window");

    if (_origin.x < 0 || _origin.y < 0) throw sizeErr;

    int x, y;
    getmaxyx(stdscr, y, x);
    Coord opposite = _origin + _size;
    if (opposite.x > x || opposite.y > y) throw sizeErr;

    if (_bordered) {
        if (_origin.x < 1 || _origin.y < 1) throw sizeErr;
        if (opposite.x + 1 > x || opposite.y + 1 > y) throw sizeErr;

        _borderWindow = newwin(_size.y + 2, _size.x + 2, _origin.y - 1, _origin.x - 1);
        if (!_borderWindow) throw windowErr;

    }

    _contentWindow = newwin(_size.y, _size.x, _origin.y, _origin.x);
    if (!_contentWindow) throw windowErr;
}


void
Window::draw() const {
    if (!isSetup()) return;

    if (_borderWindow) {
        wclear(_borderWindow);
        box(_borderWindow, 0, 0);
        wrefresh(_borderWindow);
    }

    wclear(_contentWindow);
    _drawable->draw(_contentWindow);
    wrefresh(_contentWindow);
}


Window::~Window() {
    if (_borderWindow) {
        delwin(_borderWindow);
    }

    if (_contentWindow) {
        delwin(_contentWindow);
    }
}
