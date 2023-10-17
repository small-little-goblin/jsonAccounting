#include "MenuView.h"

void drawMenu(WINDOW* win, int selected, const std::vector<std::string>& items) {
    wclear(win);
    for (int i = 0; i < items.size(); ++i) {
        if (selected == i) {
            wattron(win, COLOR_PAIR(1));
            mvwprintw(win, i + 1, 1, "%s", items[i].c_str());
            wattroff(win, COLOR_PAIR(1));
        } else {
            wattron(win, COLOR_PAIR(2));
            mvwprintw(win, i + 1, 1, "%s", items[i].c_str());
            wattroff(win, COLOR_PAIR(2));
        }
    }
    box(win, 0, 0);
    refresh();
    wrefresh(win);
}

void drawExpenses(WINDOW* win,Data& data, const Date& date) {
    wclear(win);    
    mvwprintw(win, 1, 2, "Income: %d Remaining: %d", 
            data.getIncome(date), 
            data.getIncome(date) - data.getTotalExpenses(date));
    int displayLine = 2;
    json& expenses = data.getExpenses(date);
    for (auto& expense : expenses){
        mvwprintw(win, displayLine++, 1, "Expense: %s Cost: %d",
                expense["name"].get<std::string>().c_str(),
                expense["amount"].get<int>() );
    }
    box(win, 0, 0);
    refresh();
    wrefresh(win);
}

json selectExpense(WINDOW* win, Data& data) {
    auto curDate = getDate();
    int selected {1};
    int amountItems {1};
    std::vector<json> items {{
        {"name", ""},
        {"amount", 0}            
    }};
    for (auto expense : data.getExpenses(curDate)) {
        items.push_back(expense);
    }
    mvwprintw(win, 1, 2, "Create new Expense\t\t");
    wrefresh(win);
    while(true){
        WindowUtils::highlightLine(win, selected);
        wrefresh(win);
        int ch = getch();
        switch(ch){
            case KEY_UP:
            {
                WindowUtils::unhighlightLine(win, selected);
                selected--;
                if(selected < 1)
                    selected = items.size();
                break;
            }
            case KEY_DOWN:
            {
                WindowUtils::unhighlightLine(win, selected);
                selected++;
                if(selected == items.size() + 1)
                    selected = 1;
                break;
            }
            case 10:
            {
                return items[selected - 1];
            }
            case 27: //fallthrough
            case 'q': return {};
            default: break;
        }
    }
}

void promptNewExpense(WINDOW* win, json& newExpense) {
    echo();
    wclear(win);
    box(win, 0, 0);
    if (newExpense["name"] == "") {
        char name[100];
        mvwprintw(win, 1, 2, "Expenense name: ");
        wrefresh(win);
        wgetnstr(win, name, sizeof(name));
        if (strlen(name) == 0) return;
        newExpense["name"] = name;
    }
    mvwprintw(win, 2, 2, "Expense cost: ");
    wrefresh(win);
    newExpense["amount"] = WindowUtils::wScanInt(win);
    noecho();
}

int promptIncome(WINDOW* win) {
    echo();
    wclear(win);
    box(win, 0, 0);
    int income {0};
    mvwprintw(win, 1, 1, "Enter next month's income: ");
    wrefresh(win);
    income = WindowUtils::wScanInt(win);
    noecho();
    return income;
}

int promptIncomeUpdate(WINDOW* win) {
    echo();
    wclear(win);
    box(win, 0, 0);
    int bonus {0};
    mvwprintw(win, 1, 1, "Add to or substract from current income: ");
    wrefresh(win);
    bonus = WindowUtils::wScanInt(win);
    noecho();
    return bonus;
}
