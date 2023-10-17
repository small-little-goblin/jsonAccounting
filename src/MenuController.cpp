#include "MenuController.h"
#include <iostream>

MenuController::MenuController(Data& data, WINDOW* menuWin, WINDOW* expWin) 
    : data(data), menuWin(menuWin), expWin(expWin), selected(0) {
    menuItems = {
        "Insert Expense",
        "Insert Income",
        "Add/Sub Income",
        "Quit"
    };
}

void MenuController::run() {
    data.checkNewMonth();
    int input;
    while (true) {
        drawMenu(menuWin, selected, menuItems);
        drawExpenses(expWin, data, getDate());
        input = getch();
        switch (input)
        {
            case KEY_UP:
                selected = (selected - 1 + menuItems.size()) % menuItems.size();
                break;
            case KEY_DOWN:
                selected = (selected + 1) % menuItems.size();
                break;
            case 10: //Enter
                switch(selected) 
                {
                    case 0:
                        menuInsertExpense();
                        break;
                    case 1:
                        menuInsertIncome();
                        break;
                    case 2:
                        menuUpdateIncome();
                        break;
                    case 3:
                        return;    
                }
                break;
            case 'q': //Fallthrough 
            case 27: //Escape key
                return;
            default:
                break;
        }
    }        
}

void MenuController::menuInsertExpense() {
    json newExpense = selectExpense(expWin, data);
    if (newExpense.empty()) {
        return;
    }
    promptNewExpense(expWin, newExpense);
    data.insertExpense(newExpense);
}

void MenuController::menuInsertIncome() {
    int newIncome = promptIncome(expWin);
    data.setPreliminaryIncome(newIncome);
}

void MenuController::menuUpdateIncome() {
    int deviation = promptIncomeUpdate(expWin);
    data.updateIncome(deviation);
}


