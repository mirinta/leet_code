#include <algorithm>
#include <vector>

/**
 * Given an array of meeting time intervals intervals where intervals[i] = [starti, endi], return
 * the minimum number of conference rooms required.
 *
 * ! 1 <= intervals.length <= 10^4
 * ! 0 <= starti < endi <= 10^6
 */

class Solution {
public:
    int minMeetingRooms(std::vector<std::vector<int>>& intervals)
    {
        const int n = intervals.size();
        std::vector<std::pair<int, int>> timestamps;
        timestamps.reserve(2 * n);
        for (const auto& interval : intervals) {
            timestamps.emplace_back(interval[0], 1);
            timestamps.emplace_back(interval[1], -1);
        }
        std::sort(timestamps.begin(), timestamps.end());
        int count = 0;
        int result = 0;
        for (const auto& [time, flag] : timestamps) {
            count += flag;
            result = std::max(result, count);
        }
        return result;
    }
};
