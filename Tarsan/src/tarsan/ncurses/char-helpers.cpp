//
//  char-helpers.cpp
//  Quizzy
//
//  Created by Jakub Charvát on 10.06.2022.
//

#include "char-helpers.hpp"

#include <ncurses.h>
#include <cctype>


bool
CharHelpers::isTextfieldPrintable (int c) {
    return std::isalnum(c) || isSpace(c) || ispunct(c);
}


bool
CharHelpers::isBackspace (int c) {
    return c == KEY_BACKSPACE
        || c == '\a'
        || c == '\b'
        || c == 127;
}


bool
CharHelpers::isEnter (int c) {
    return c == KEY_ENTER
        || c == '\n'
        || c == '\r';
}


bool
CharHelpers::isSpace (int c) {
    return c == ' ';
}


bool
CharHelpers::isDelete (int c) {
    return c == KEY_DL || c ==  KEY_DC;
}


bool
CharHelpers::isEscape (int c) {
    if (c != 27) return false;

    nodelay(stdscr, true);
    int n = getch();
    nodelay(stdscr, false);
    return n == -1;
}


bool
CharHelpers::isBuild(int c) {
    if (!isalpha(c)) return false;
    char l = tolower(c);
    return l == 'q' || l == 'w' || l == 'e'
        || l == 'a'             || l == 'd'
        || l == 'z' || l == 'x' || l == 'c';
}
