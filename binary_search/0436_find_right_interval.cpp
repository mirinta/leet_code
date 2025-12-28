#include <algorithm>
#include <unordered_map>
#include <vector>

/**
 * You are given an array of intervals, where intervals[i] = [start_i, end_i] and each start_i is
 * unique.
 *
 * The right interval for an interval i is an interval j such that start_j >= end_i and start_j is
 * minimized. Note that i may equal j.
 *
 * Return an array of right interval indices for each interval i. If no right interval exists for
 * interval i, then put -1 at index i.
 *
 * ! 1 <= intervals.length <= 2 * 10^4
 * ! intervals[i].length == 2
 * ! -10^6 <= start_i <= end_i <= 10^6
 * ! The start point of each interval is unique.
 */

class Solution {
public:
    std::vector<int> findRightInterval(std::vector<std::vector<int>>& intervals)
    {
        const int n = intervals.size();
        std::unordered_map<int, int> map;
        for (int i = 0; i < n; ++i) {
            map[intervals[i][0]] = i;
        }
        std::sort(intervals.begin(), intervals.end());
        std::vector<int> result(n);
        for (const auto& interval : intervals) {
            const int start = interval[0];
            const int end = interval[1];
            auto iter = std::lower_bound(intervals.begin(), intervals.end(), end,
                                         [](const auto& v, int val) { return v[0] < val; });
            if (iter == intervals.end()) {
                result[map[start]] = -1;
            } else {
                result[map[start]] = map[(*iter)[0]];
            }
        }
        return result;
    }
};
