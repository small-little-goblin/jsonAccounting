#ifndef DATA_H
#define DATA_H

#include <nlohmann/json.hpp>
#include "DateUtils.h"

using json = nlohmann::json;

class Data {
public:
    Data();
    ~Data();
    void setIncome(int income);
    void setPreliminaryIncome(int prelIncome);
    void updateIncome(int deviation);
    void insertExpense(json newExpense);
    void checkNewMonth();
    json init();
    bool dateExists(const Date& date = getDate(-1)) const;
    int getPreliminaryIncome(const Date& date = getDate()) const;
    int getIncome(const Date& date = getDate()) const;
    json& getExpenses(const Date& date = getDate());
    int getTotalExpenses(const Date& date = getDate()) const;

private:
    json data;
    json& dataForDate(const Date& date = getDate());
    json& dataForDate(int offset);
    const json& dataForDate(const Date& date = getDate()) const ;
    const json& dataForDate(int offset) const;
};
#endif // DATA_H

