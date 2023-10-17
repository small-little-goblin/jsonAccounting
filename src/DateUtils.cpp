#include "DateUtils.h"

Date getDate(int offset) {
    using namespace std::chrono;
    auto date = year_month_day{floor<days>(system_clock::now())};
    date += months(offset);
    int year = int(date.year());
    int month = unsigned(date.month());
    return Date {std::to_string(year), std::to_string(month)};
}
