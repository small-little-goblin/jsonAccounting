#include "WindowUtils.h"


    int WindowUtils::wScanInt(WINDOW* window) {
        char inputStr[100];
        wgetnstr(window, inputStr, sizeof(inputStr));

        int number;
        try {
            number = std::stoi(inputStr);
        } catch (const std::invalid_argument& ex) {
            number = 0; // Set a default value or take appropriate action
        }

        return number;
    }

    void WindowUtils::highlightLine(WINDOW* win, int line) {
        int x, y;
        getyx(win, y, x);
        char buffer[100];
        mvwinstr(win, line, 1, buffer);
        wattron(win, A_STANDOUT);
        mvwprintw(win, line, 1, "%s", buffer);
        wattroff(win, A_STANDOUT);
        wmove(win, y, x);
        wrefresh(win);
    }

    void WindowUtils::unhighlightLine(WINDOW* win, int line) {
        int x, y;
        getyx(win, y, x);
        char buffer[100];
        mvwinstr(win, line, 1, buffer);
        mvwprintw(win, line, 1, "%s", buffer);
        wmove(win, y, x);
        wrefresh(win);
    }

    std::string WindowUtils::getStrFromLine(WINDOW* win, int line) {
        int x, y;
        getyx(win, y, x);
        char buffer[100];
        mvwinnstr(win, line, 1, buffer, sizeof(buffer));
        return buffer; 
    }

 // namespace windowUtils
