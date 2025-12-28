#include <algorithm>
#include <vector>

/**
 * You are implementing a program to use as your calendar. We can add a new event if adding the
 * event will not cause a triple booking.
 *
 * A triple booking happens when three events have some non-empty intersection (i.e., some moment is
 * common to all the three events.).
 *
 * The event can be represented as a pair of integers start and end that represents a booking on the
 * half-open interval [start, end), the range of real numbers x such that start <= x < end.
 *
 * Implement the MyCalendarTwo class:
 *
 * - MyCalendarTwo() Initializes the calendar object.
 *
 * - boolean book(int start, int end) Returns true if the event can be added to the calendar
 * successfully without causing a triple booking. Otherwise, return false and do not add the event
 * to the calendar.
 *
 * ! 0 <= start < end <= 10^9
 * ! At most 1000 calls will be made to book.
 */

class MyCalendarTwo {
public:
    MyCalendarTwo() {}

    bool book(int start, int end)
    {
        std::vector<std::pair<int, int>> temp;
        for (int i = 0; i < data.size(); ++i) {
            if (data[i].second <= start || data[i].first >= end)
                continue;

            temp.emplace_back(data[i]);
        }
        std::sort(temp.begin(), temp.end());
        for (int i = 1; i < temp.size(); ++i) {
            if (temp[i].first < temp[i - 1].second)
                return false;
        }
        data.emplace_back(start, end);
        return true;
    }

private:
    std::vector<std::pair<int, int>> data;
};

/**
 * Your MyCalendarTwo object will be instantiated and called as such:
 * MyCalendarTwo* obj = new MyCalendarTwo();
 * bool param_1 = obj->book(start,end);
 */