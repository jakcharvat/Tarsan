//
//  input-window.cpp
//  Tarsan
//
//  Created by Jakub Charvát on 12.06.2022.
//

#include "input-window.hpp"

#include "../logging/out.hpp"


InputWindow::InputWindow():
Window(nullptr, nullptr, { 0, 0 }, { 0, 0 }, false) { }


void
InputWindow::setup() {
    Window::setup();
    nodelay(_contentWindow, true);
    keypad(_contentWindow, true);
}


int
InputWindow::getchar() {
    int c = wgetch(_contentWindow);
    if (c == KEY_DOWN) out() << "KEY DOWN" << std::endl;
    return c;
}


void
InputWindow::buffer(int c) {
    _buffer.push(c);
}


int
InputWindow::poll() {
    if (_buffer.empty()) return -1;

    int front = _buffer.front();
    _buffer.pop();
    return front;
}
