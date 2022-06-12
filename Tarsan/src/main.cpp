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


int main() {
    srandom(static_cast<unsigned int>(time(nullptr)));

    try {
        App app;
        app.run();
    } catch (const FatalError & error) {
        std::cerr << "Fatal error: " << error.what() << std::endl;
        std::cerr << "The app cannot continue, sorry :(" << std::endl;
        return 2;
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
