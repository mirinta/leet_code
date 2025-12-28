#include <algorithm>
#include <vector>

/**
 * There is a one-dimensional garden on the x-axis. The garden starts at the point 0 and ends at the
 * point n. (i.e The length of the garden is n).
 *
 * There are n + 1 taps located at points [0, 1, ..., n] in the garden.
 *
 * Given an integer n and an integer array ranges of length n + 1 where ranges[i] (0-indexed) means
 * the i-th tap can water the area [i - ranges[i], i + ranges[i]] if it was open.
 *
 * Return the minimum number of taps that should be open to water the whole garden, If the garden
 * cannot be watered return -1.
 *
 * ! 1 <= n <= 10^4
 * ! ranges.length == n + 1
 * ! 0 <= ranges[i] <= 100
 */

class Solution {
public:
    int minTaps(int n, std::vector<int>& ranges)
    {
        std::vector<std::pair<int, int>> intervals(n + 1);
        for (int i = 0; i <= n; ++i) {
            intervals[i].first = std::max(0, i - ranges[i]);
            intervals[i].second = std::min(n, i + ranges[i]);
        }
        std::sort(intervals.begin(), intervals.end(), [](const auto& p1, const auto& p2) {
            return p1.first == p2.first ? p1.second > p2.second : p1.first < p2.first;
        });
        int result = 0;
        int endingPoint = 0;
        int i = 0;
        while (i <= n) {
            int farthest = endingPoint;
            while (i <= n && intervals[i].first <= endingPoint) {
                farthest = std::max(farthest, intervals[i].second);
                i++;
            }
            if (farthest > endingPoint) {
                result++;
                endingPoint = farthest;
            } else {
                return -1;
            }
            if (endingPoint >= n)
                return result;
        }
        return -1;
    }
};