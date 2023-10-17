#ifndef WINDOWUTILS_HPP
#define WINDOWUTILS_HPP

#include <ncurses.h>
#include <string>
#include <stdexcept>

namespace WindowUtils {

    int wScanInt(WINDOW* window);
    void highlightLine(WINDOW* win, int line);
    void unhighlightLine(WINDOW* win, int line);
    std::string getStrFromLine(WINDOW* win, int line);

}

#endif // WINDOWUTILS_HPP

