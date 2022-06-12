//
//  input-window.cpp
//  Tarsan
//
//  Created by Jakub Charvát on 12.06.2022.
//

#include "input-window.hpp"


InputWindow::InputWindow():
Window(nullptr, nullptr, { 0, 0 }, { 0, 0 }, false) { }


void
InputWindow::setup() {
    Window::setup();
    nodelay(_contentWindow, true);
}


int
InputWindow::getchar() {
    return wgetch(_contentWindow);
}
