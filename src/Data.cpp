#include "Data.h"
#include <fstream>
#include <filesystem>
#include <iostream>

json Data::init(){
    auto[year, month] = getDate();
    json data;
    data[year][month]["income"] = 0;
    data[year][month]["expenses"];
    return data;
}

Data::Data() {
    if (!std::filesystem::exists("data/acc.json")) {
        std::ofstream createFile("data/acc.json");
        createFile << init();
        createFile.close();
    }
    std::ifstream f("data/acc.json");
    data = json::parse(f);
}

Data::~Data() {
    std::ofstream save("data/acc.json");
    save << data.dump(2);
    save.close();
}

void Data::setIncome(int amount){
    dataForDate()["income"] = amount; 
}

void Data::setPreliminaryIncome(int amount){
    dataForDate(1)["preliminaryIncome"] = amount;
}   

void Data::updateIncome(int deviation){
    dataForDate()["income"] = dataForDate()["income"].get<int>() + deviation;
}

void Data::insertExpense(json newExpense){
    if (newExpense["name"] == "") return;
    auto& expenses = getExpenses();
    for (auto& expense : expenses) {
        if (expense["name"] == newExpense["name"]) {
            expense["amount"] = expense["amount"].get<int>() + newExpense["amount"].get<int>();
            return;
        } 
    }
    expenses.push_back(newExpense);
}

bool Data::dateExists(const Date& date) const {
    auto [year, month] = date;
    return (data.contains(year) && data[year].contains(month));
}

int Data::getPreliminaryIncome(const Date& date) const {
    if (dataForDate(date).contains("preliminaryIncome")) {
        return dataForDate(date)["preliminaryIncome"].get<int>();
    }
    return 0;
}

int Data::getIncome (const Date& date) const {
    if (dataForDate(date).contains("income")) {
        return dataForDate(date)["income"].get<int>();
    }
    else
        return 0;
}

json& Data::getExpenses(const Date& date) {
    return dataForDate(date)["expenses"];
}


int Data::getTotalExpenses(const Date& date) const {
    int totalCost {0};
    for (auto& expense : dataForDate(date)["expenses"]){
        totalCost += expense["amount"].get<int>();
    }
    return totalCost;
}

json& Data::dataForDate(const Date& date){
    auto [year, month] = date;
    return data[year][month];
}

json& Data::dataForDate(int offset){
    auto [year, month] = getDate(offset);
    return data[year][month];
}

const json& Data::dataForDate(const Date& date) const {
    auto [year, month] = date;
    return data[year][month];
}

const json& Data::dataForDate(int offset) const {
    auto [year, month] = getDate(offset);
    return data[year][month];
}


void Data::checkNewMonth() {
    if (!dateExists()) {
        return;
    }
    if ( dataForDate().contains("income") 
         && dataForDate().contains("expenses")) 
    {
        return;
    }
    dataForDate()["income"];
    dataForDate()["expenses"];

    if (int pIncome = getPreliminaryIncome()) {
        setIncome(pIncome);
        dataForDate().erase("preliminaryIncome");
        dataForDate(1)["preliminaryIncome"] = pIncome;
        int overflow = getIncome(getDate(-1)) - getTotalExpenses(getDate(-1));
        updateIncome(overflow);
    }
}
