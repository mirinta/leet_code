#include <algorithm>
#include <vector>

/**
 * Given an array intervals where intervals[i] = [li, ri] represent the interval [li, ri), remove all intervals that are
 * covered by another interval in the list.
 *
 * The interval [a, b) is covered by the interval [c, d) if and only if c <= a and b <= d.
 *
 * Return the number of remaining intervals.
 *
 * ! 1 <= intervals.length <= 1000
 * ! intervals[i].length == 2
 * ! 0 <= li < ri <= 10^5
 * ! All the given intervals are unique.
 */

class Solution {
public:
    int removeCoveredIntervals(std::vector<std::vector<int>>& intervals)
    {
        // interval1: [a, b]
        // interval2: [x, y]
        // interval1 is covered by interval2 means:
        // x <= a && y >= b
        std::sort(intervals.begin(), intervals.end(), [](const auto& v1, const auto& v2) {
            if (v1[0] == v2[0])
                return v1[1] > v2[1];

            return v1[0] < v2[0];
        });
        const int n = intervals.size();
        int result = 0;
        for (int i = 0, end = 0; i < n; ++i) {
            if (intervals[i][1] > end) {
                result++;
                end = intervals[i][1];
            }
        }
        return result;
    }
};