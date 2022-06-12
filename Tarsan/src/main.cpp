//
//  main.cpp
//  Quizzy
//
//  Created by Jakub Charvát on 04.06.2022.
//

#ifndef __TEST__

#include <iostream>

#include "tarsan/logging/fatal-error.hpp"
#include "tarsan/ncurses/app.hpp"

#include "tarsan/game/map-generator.hpp"
#include "tarsan/game/map-saver.hpp"


/// @mainpage Tarsan
///
/// @section intro Introduction
/// This is a very simple sandbox game. Here you play as a small hero trapped in a box in which there are only liannas and lava. You can build and destroy stones, and your goal is to stay alive for as long as you can.
///
/// @section install Installation
/// @subsection compilation Compilation
/// Download the source, then in your terminal of choice with bash installed, run
/// ```bash
/// make compile
/// ```
///
/// @subsection running Running
/// If you have the binary built from the compilation step then you can simply open it and enjoy. Otherwise it is possible to directly build and launch the binary by running
/// ```bash
/// make run
/// ```
///
/// @section controls Controls
/// To move around the world use the arrow keys. Building is done using the following keys for the blocks around the player (assume P is the player):
/// ```txt
/// q w e
/// a P d
/// z x c
/// ```
/// The same keys, only with shift, are used to excavate the blocks at those same positions. Use l to shoot a liana to the sky.
///
/// @section config Config
/// It is possible to customise the behaviour of the map generator. To do so, edit the `generator.config` file in the `examples` directory. The format, as well as supported keys, are described in that file.


int main() {
    srandom(static_cast<unsigned int>(time(nullptr)));

    MapGenerator generator;

    while (true) {
        try {
            App app;
            if (!app.run(generator)) break;
        } catch (const FatalError & error) {
            std::cerr << "Fatal error: " << error.what() << std::endl;
            std::cerr << "The app cannot continue, sorry :(" << std::endl;
            return 2;
        }
    }
}


//int main () {
//    using namespace std::string_literals;
//
//    initscr();
//    use_default_colors();
//    start_color();
//    noecho();
//    cbreak();
//    keypad(stdscr, true);
//
//    curs_set(0);
//
//
//    TopLevelResponder tlr;
//    QuestionPage page(&tlr);
//
//    RadioSelectQuestion radioQuestion (&page, "2 + 2 is", { "3", "4", "5", "6" }, 2);
//    CheckmarkSelectQuestion checkQuestion (&page, "Choose the aliens", {
//        "Steve Jobs",
//        "Lada Vagner",
//        "Mark Zuckerberg",
//        "Elon Musk"
//    }, { 2, 3 }, 10.f);
//    TextQuestion textQuestion (&page, "Name the one true God");
//
//    page.setQuestions({
//        &radioQuestion,
//        &checkQuestion,
//        &textQuestion,
//    });
//
//    page.requestAttentionToFirstChild();
//
//
//    while (true) {
//        curs_set(0);
//
//        Size size;
//        getmaxyx(stdscr, size.y, size.x);
//        size = size - Size { 2, 2 };
//        Size origin = { 1, 1 };
//
//        page.draw(stdscr, origin.y, origin.x, size);
//
//        tlr.leafResponder()->showCursor();
//
//        refresh();
//
//        int c = getch();
//        if (CharHelpers::isEscape(c)) break;
//
//        KeyEvent e (c);
//        tlr.handleEvent(e);
//        if (e.shouldPropagate() && c == 'q') break;
//    }
//
//    curs_set(1);
//
//    endwin();
//}


#endif
