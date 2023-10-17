#ifndef MENUCONTROLLER_HPP
#define MENUCONTROLLER_HPP

#include "Data.h"
#include "MenuView.h"
#include <ncurses.h>
#include <vector>
#include <string>

class MenuController {
public:
    MenuController(Data& data, WINDOW* menuWin, WINDOW* expWin);
    void run();

private:
    Data& data;
    WINDOW* menuWin;
    WINDOW* expWin;
    int selected;
    std::vector<std::string> menuItems;

    void menuInsertExpense();
    void menuInsertIncome();
    void menuUpdateIncome();
};

#endif // MENUCONTROLLER_HPP

