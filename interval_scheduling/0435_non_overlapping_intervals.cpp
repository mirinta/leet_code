#include <algorithm>
#include <vector>

/**
 * Given an array of intervals intervals where intervals[i] = [starti, endi], return the minimum
 * number of intervals you need to remove to make the rest of the intervals non-overlapping.
 *
 * ! 1 <= intervals.length <= 10^5
 * ! intervals[i].length == 2
 * ! -5 * 10^4 <= starti < endi <= 5 * 10^4
 */

class Solution {
public:
    int eraseOverlapIntervals(std::vector<std::vector<int>>& intervals)
    {
        // sort by ending point
        std::sort(intervals.begin(), intervals.end(), [](const auto& v1, const auto& v2) { return v1[1] < v2[1]; });
        int result = 0;
        int endingPoint = intervals[0][1];
        for (int i = 1; i < intervals.size(); ++i) {
            if (intervals[i][0] < endingPoint) {
                result++;
            } else {
                endingPoint = intervals[i][1];
            }
        }
        return result;
    }
};