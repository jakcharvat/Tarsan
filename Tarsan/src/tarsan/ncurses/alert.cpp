//
//  alert.cpp
//  Tarsan
//
//  Created by Jakub Charvát on 12.06.2022.
//

#include "alert.hpp"
#include "../logging/fatal-error.hpp"
#include "../ncurses/char-helpers.hpp"
#include "../ncurses/color.hpp"


Coord
Alert::_calculateBoundingBox(const std::string &text, int w) const {
    int size = static_cast<int>(text.size());
    if (size <= w) return { size, 1 };

    // Ceiling division from
    // https://stackoverflow.com/a/2745086/9020201
    return { w, 1 + ((size - 1) / w), };
}


Alert::Alert(std::string error, std::string hint):
_error(error),
_hint(hint) { }


bool
Alert::waitForUserInteraction(InputWindow &input) {
    int c = input.blockingGetchar();
    return !CharHelpers::isEscape(c);
}


void
Alert::draw(WINDOW *window) {
    int w, h;
    getmaxyx(window, h, w);

    Coord errBoundingRect = _calculateBoundingBox(_error, w);
    Coord hintBoundingRect = _calculateBoundingBox(_hint, w);

    int height = errBoundingRect.y + hintBoundingRect.y + 1;

    if (height > h) throw FatalError ("Window too small for error message");

    int paddingTop = (h - height) / 2;
    int errorPaddingLeft = (w - errBoundingRect.x) / 2;
    int hintPaddingTop = paddingTop + errBoundingRect.y + 1;
    int hintPaddingLeft = (w - hintBoundingRect.x) / 2;

    wattrset(window, Color::pair(COLOR_WHITE, COLOR_DEFAULT));
    mvwprintw(window, paddingTop, errorPaddingLeft, "%s", _error.c_str());
    wattron(window, A_BOLD);
    mvwprintw(window, hintPaddingTop, hintPaddingLeft, "%s", _hint.c_str());
}
