#include <map>

/**
 * You are implementing a program to use as your calendar. We can add a new event if adding the
 * event will not cause a double booking.
 *
 * A double booking happens when two events have some non-empty intersection (i.e., some moment is
 * common to both events.).
 *
 * The event can be represented as a pair of integers start and end that represents a booking on the
 * half-open interval [start, end), the range of real numbers x such that start <= x < end.
 *
 * Implement the MyCalendar class:
 *
 * - MyCalendar() Initializes the calendar object.
 *
 * - boolean book(int start, int end) Returns true if the event can be added to the calendar
 *   successfully without causing a double booking. Otherwise, return false and do not add the event
 *   to the calendar.
 *
 * ! 0 <= start < end <= 10^9
 * ! At most 1000 calls will be made to book.
 */

class MyCalendar {
public:
    MyCalendar() {}

    bool book(int start, int end)
    {
        //     start               end
        //     |-------------------|
        //  |-----|            |-------|
        //  x1    y1           x2      y2
        auto iter = map.upper_bound(start);
        if (iter != map.begin() && std::prev(iter)->second > start)
            return false;

        if (iter != map.end() && end > iter->first)
            return false;

        map[start] = end;
        return true;
    }

private:
    std::map<int, int> map;
};

/**
 * Your MyCalendar object will be instantiated and called as such:
 * MyCalendar* obj = new MyCalendar();
 * bool param_1 = obj->book(start,end);
 */
