#include "Date.h"
#include <string>
#include "../exceptions/ValidationException.h"

Date::Date() : Date(1, 1, 2026) {}

Date::Date(int day, int month, int year)
{
    if (month < 1 || month > 12)
    {
        throw ValidationException("Invalid month.");
    }
    if (day < 1 || day > 31)
    {
        throw ValidationException("Invalid day.");
    }
    if (year < 0)
    {
        throw ValidationException("Invalid year.");
    }

    this->day = day;
    this->month = month;
    this->year = year;
}

bool Date::operator==(const Date& other) const
{
    return day == other.day && month == other.month && year == other.year;
}

auto Date::operator<=>(const Date& other) const
{
    if (year != other.year)
    {
        return year <=> other.year;
    }
    if (month != other.month)
    {
        return month <=> other.month;
    }

    return day <=> other.day;
}

std::string Date::toString() const
{
    std::string result;
    if (day < 10)
    {
        result += '0';
    }
    result += std::to_string(day);
    result += '/';
    if (month < 10)
    {
        result += '0';
    }
    result += std::to_string(month);
    result += '/';
    result += std::to_string(year);

    return result;
}

Date Date::parse(const std::string& str)
{
    if (str.size() != 10)
    {
        throw ValidationException("Invalid date format.");
    }
    if (str[2] != '/' || str[5] != '/')
    {
        throw std::invalid_argument("Invalid date format.");
    }
    int day = std::stoi(str.substr(0, 2));
    int month = std::stoi(str.substr(3, 2));
    int year = std::stoi(str.substr(6, 4));

    return Date(day, month, year);
}

bool Date::isBefore(const Date& other) const
{
    return *this < other;
}

bool Date::isAfter(const Date& other) const
{
    return *this > other;
}

int Date::daysUntil(const Date& other) const
{
    int thisTotalDays = year * 365 + month * 30 + day;
    int otherTotalDays = other.year * 365 + other.month * 30 + other.day;

    return otherTotalDays - thisTotalDays;
}