#include <algorithm>
#include <vector>

/**
 * Given an array of meeting time intervals where intervals[i] = [starti, endi], determine if a
 * person could attend all meetings.
 *
 * ! 0 <= intervals.length <= 10^4
 * ! intervals[i].length == 2
 * ! 0 <= starti < endi <= 10^6
 */

class Solution {
public:
    bool canAttendMeetings(std::vector<std::vector<int>>& intervals)
    {
        // if there's no intersection between the given intervals, return true
        // otherwise, return false
        const int n = intervals.size();
        std::vector<std::pair<int, int>> points;
        points.reserve(2 * n);
        for (const auto& interval : intervals) {
            points.emplace_back(interval[0], 1);
            points.emplace_back(interval[1], -1);
        }
        std::sort(points.begin(), points.end());
        int count = 0;
        for (const auto& point : points) {
            count += point.second;
            if (count > 1)
                return false;
        }
        return true;
    }
};
