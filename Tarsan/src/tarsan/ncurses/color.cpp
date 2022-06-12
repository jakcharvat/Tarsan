//
//  color.cpp
//  Quizzy
//
//  Created by Jakub Charvát on 05.06.2022.
//

#include "color.hpp"

#include <algorithm>


Color
Color::_instance;


Color::Color () {
    std::fill(_pairs.begin(), _pairs.end(), -1);
}


short
Color::_get(short foreground, short background) {
    int index = (foreground - COLOR_DEFAULT) * VALID_COLORS + (background - COLOR_DEFAULT);
    short & stored = _pairs[index];

    if (stored == -1) {
        init_pair(_nextIndex, foreground, background);
        stored = _nextIndex++;
    }

    return stored;
}


int
Color::_pair(short foreground, short background) {
    return COLOR_PAIR(_get(foreground, background));
}


short
Color::get(short foreground, short background) {
    return _instance._get(foreground, background);
}


int
Color::pair(short foreground, short background) {
    return _instance._pair(foreground, background);
}
