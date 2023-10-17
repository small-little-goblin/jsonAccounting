#ifndef MENUVIEW_HPP
#define MENUVIEW_HPP

#include "WindowUtils.h"
#include <ncurses.h>
#include "Data.h"
    
void drawMenu(WINDOW* win, int selected, const std::vector<std::string>& items);
void drawExpenses(WINDOW* win, Data& data, const Date& date);
json selectExpense(WINDOW* win, Data& data);
void promptNewExpense(WINDOW* win, json& newExpense);
int promptIncome(WINDOW* win);
int promptIncomeUpdate(WINDOW* win);    

#endif // MENUVIEW_HPP

