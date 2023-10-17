#ifndef DATEUTILS_HPP
#define DATEUTILS_HPP

#include <chrono>
#include <functional>
#include <string>

struct Date {
    const std::string year;
    const std::string month;
};

Date getDate(int offset = 0);

#endif // DATEUTILS_HPP

