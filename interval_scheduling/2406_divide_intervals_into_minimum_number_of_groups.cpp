#include <algorithm>
#include <vector>

/**
 * You are given a 2D integer array intervals where intervals[i] = [lefti, righti] represents the
 * inclusive interval [lefti, righti].
 *
 * You have to divide the intervals into one or more groups such that each interval is in exactly
 * one group, and no two intervals that are in the same group intersect each other.
 *
 * Return the minimum number of groups you need to make.
 *
 * Two intervals intersect if there is at least one common number between them. For example, the
 * intervals [1, 5] and [5, 8] intersect.
 *
 * ! 1 <= intervals.length <= 10^5
 * ! intervals[i].length == 2
 * ! 1 <= lefti <= righti <= 10^6
 */

class Solution {
public:
    int minGroups(std::vector<std::vector<int>>& intervals)
    {
        // min num of groups = max num of overlapping intervals at the same time
        const int n = intervals.size();
        std::vector<std::pair<int, int>> timestamps; // <time, +1/-1 flag>
        timestamps.reserve(2 * n);
        for (const auto& interval : intervals) {
            timestamps.emplace_back(interval[0], 1);
            timestamps.emplace_back(interval[1], -1);
        }
        std::sort(timestamps.begin(), timestamps.end(), [](const auto& t1, const auto& t2) {
            if (t1.first == t2.first)
                return t1.second > t2.second; // process +1 flag first

            return t1.first < t2.first;
        });
        int result = 0;
        int count = 0;
        for (const auto& [time, flag] : timestamps) {
            count += flag;
            result = std::max(result, count);
        }
        return result;
    }
};
