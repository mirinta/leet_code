#include <algorithm>
#include <vector>

/**
 * You are given an array of non-overlapping intervals intervals where intervals[i] = [start_i,
 * end_i] represent the start and the end of the ith interval and intervals is sorted in ascending
 * order by start_i. You are also given an interval newInterval = [start, end] that represents the
 * start and end of another interval.
 *
 * Insert newInterval into intervals such that intervals is still sorted in ascending order by
 * start_i and intervals still does not have any overlapping intervals (merge overlapping intervals
 * if necessary).
 *
 * Return intervals after the insertion.
 *
 * ! 0 <= intervals.length <= 10^4
 * ! intervals[i].length == 2
 * ! 0 <= start_i <= end_i <= 10^5
 * ! intervals is sorted by start_i in ascending order.
 * ! newInterval.length == 2
 * ! 0 <= start <= end <= 10^5
 */

class Solution {
public:
    std::vector<std::vector<int>> insert(std::vector<std::vector<int>>& intervals, std::vector<int>& newInterval)
    {
        auto iter = std::upper_bound(intervals.begin(), intervals.end(), newInterval[0],
                                     [](int val, const auto& v) { return val < v[0]; });
        intervals.insert(iter, newInterval);
        std::vector<std::vector<int>> result;
        for (int i = 0; i < intervals.size(); ++i) {
            if (result.empty() || intervals[i][0] > result.back()[1]) {
                result.push_back(intervals[i]);
            } else {
                result.back()[1] = std::max(result.back()[1], intervals[i][1]);
            }
        }
        return result;
    }
};