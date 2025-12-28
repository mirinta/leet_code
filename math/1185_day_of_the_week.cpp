#include <array>
#include <string>

/**
 * Given a date, return the corresponding day of the week for that date.
 *
 * The input is given as three integers representing the day, month and year respectively.
 *
 * Return the answer as one of the following values {"Sunday", "Monday", "Tuesday", "Wednesday",
 * "Thursday", "Friday", "Saturday"}.
 *
 * ! The given dates are valid dates between the years 1971 and 2100.
 */

class Solution {
public:
    std::string dayOfTheWeek(int day, int month, int year)
    {
        // 1971/1/1 is a Friday
        static const std::array<std::string, 7> kDaysOfWeek{"Thursday", "Friday",  "Saturday", "Sunday",
                                                            "Monday",   "Tuesday", "Wednesday"};
        int total = 0;
        for (int i = 1971; i < year; ++i) {
            total += daysOfYear(i);
        }
        for (int i = 1; i < month; ++i) {
            total += daysOfMonth(i, year);
        }
        total += day;
        return kDaysOfWeek[total % 7];
    }

private:
    bool isLeapYear(int year)
    {
        if (year % 4 != 0)
            return false;

        if (year % 100 == 0)
            return year % 400 == 0;

        return true;
    }

    int daysOfYear(int year)
    {
        return isLeapYear(year) ? 366 : 365;
    }

    int daysOfMonth(int month, int year)
    {
        if (month == 2)
            return isLeapYear(year) ? 29 : 28;

        if (month == 4 || month == 6 || month == 9 || month == 11)
            return 30;

        return 31;
    }
};