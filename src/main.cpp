#include "MenuController.h"
#include "MenuView.h"
#include "DateUtils.h"
#include "Data.h"
#include <fstream>
#include <iostream>
#include <filesystem>

int main() {
    initscr();
    cbreak();
    curs_set(0);
    noecho();
    keypad(stdscr, TRUE);
    start_color();
    init_pair(1, COLOR_BLACK, COLOR_WHITE);
    init_pair(2, COLOR_WHITE, COLOR_BLACK);
    
    int scrHeight, scrLength;
    getmaxyx(stdscr, scrHeight, scrLength);
    WINDOW* menuWin = newwin(scrHeight / 3, scrLength / 4, 3, 2);
    WINDOW* expWin = newwin(scrHeight / 3, scrLength / 4, 3, scrLength / 4 + 1);
    
    Data data;  
    MenuController menuController(data, menuWin, expWin);
    menuController.run();
    
    endwin();
    
    return 0;
}

