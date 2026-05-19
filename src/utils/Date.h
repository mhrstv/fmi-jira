#pragma once
#include <string>
class Date {
private:
    int day;
    int month;
    int year;

public:
    Date();
    Date(int day, int month, int year);

    auto operator<=>(const Date& other) const;
    bool operator==(const Date& other) const;

    std::string toString() const;
    static Date parse(const std::string& str);

    bool isBefore(const Date& other) const;
    bool isAfter(const Date& other) const;

    int daysUntil(const Date& other) const;
};