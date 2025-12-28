#include <algorithm>
#include <vector>

/**
 * Given an array of intervals where intervals[i] = [start_i, end_i], merge all overlapping
 * intervals, and return an array of the non-overlapping intervals that cover all the intervals in
 * the input.
 *
 * ! 1 <= intervals.length <= 10^4
 * ! intervals[i].length == 2
 * ! 0 <= start_i <= end_i <= 10^4
 */

class Solution {
public:
    std::vector<std::vector<int>> merge(std::vector<std::vector<int>>& intervals)
    {
        return approach1(intervals);
    }

private:
    // sweep line, time O(NlogN), space O(N)
    std::vector<std::vector<int>> approach2(const std::vector<std::vector<int>>& intervals)
    {
        std::vector<std::pair<int, int>> points; // <coord,flag>, flag=1(starting point),-1(ending point)
        points.reserve(intervals.size() * 2);
        for (const auto& interval : intervals) {
            points.emplace_back(interval[0], 1);
            points.emplace_back(interval[1], -1);
        }
        std::sort(points.begin(), points.end(), [](const auto& p1, const auto& p2) {
            return p1.first == p2.first ? p1.second > p2.second : p1.first < p2.first;
        });
        int startingPoint = 0;
        int endingPoint = 0;
        int count = 0;
        std::vector<std::vector<int>> result;
        for (const auto& [coord, flag] : points) {
            if (count == 0 && count + flag > 0) {
                // this point starts a new interval
                startingPoint = coord;
            } else if (count > 0 && count + flag == 0) {
                // this point is the end of the current interval
                endingPoint = coord;
                result.push_back({startingPoint, endingPoint});
            }
            count += flag;
        }
        return result;
    }

    // sorting, time O(NlogN), space O(N)
    std::vector<std::vector<int>> approach1(std::vector<std::vector<int>>& intervals)
    {
        if (intervals.empty())
            return {};

        std::sort(intervals.begin(), intervals.end(), [](const auto& v1, const auto& v2) { return v1[0] < v2[0]; });
        // i0<---->i1
        //     j0<---->j1
        //                 k0<---->k1
        // after merging:
        // i0<-------->j1  k0<---->k1
        const int n = intervals.size();
        std::vector<std::vector<int>> result;
        for (int i = 0; i < n; ++i) {
            if (result.empty() || intervals[i][0] > result.back()[1]) {
                result.push_back(intervals[i]);
            } else {
                result.back()[1] = std::max(result.back()[1], intervals[i][1]);
            }
        }
        return result;
    }
};
