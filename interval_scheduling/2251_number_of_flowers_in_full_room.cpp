#include <algorithm>
#include <vector>

/**
 * You are given a 0-indexed 2D integer array flowers, where flowers[i] = [start_i, end_i] means the
 * ith flower will be in full bloom from start_i to end_i (inclusive). You are also given a
 * 0-indexed integer array people of size n, where people[i] is the time that the ith person will
 * arrive to see the flowers.
 *
 * Return an integer array answer of size n, where answer[i] is the number of flowers that are in
 * full bloom when the ith person arrives.
 *
 * ! 1 <= flowers.length <= 5 * 10^4
 * ! flowers[i].length == 2
 * ! 1 <= start_i <= end_i <= 10^9
 * ! 1 <= people.length <= 5 * 10^4
 * ! 1 <= people[i] <= 10^9
 */

class Solution {
public:
    std::vector<int> fullBloomFlowers(std::vector<std::vector<int>>& flowers, std::vector<int>& people)
    {
        const int n = flowers.size();
        const int m = people.size();
        std::vector<std::pair<int, int>> timestamps; // <time, flag>
        timestamps.reserve(2 * n);
        for (int i = 0; i < n; ++i) {
            // flower[i] = [start_i, end_i] is the duration of blooming
            // if the flower is blooming, flag = +1
            // otherwise, flag = -1
            timestamps.emplace_back(flowers[i][0], 1);
            timestamps.emplace_back(flowers[i][1] + 1, -1);
        }
        std::sort(timestamps.begin(), timestamps.end());
        std::vector<std::pair<int, int>> prefix(timestamps);
        for (int i = 1; i < prefix.size(); ++i) {
            prefix[i].first = timestamps[i].first;
            prefix[i].second = prefix[i - 1].second + timestamps[i].second;
        }
        std::vector<int> result(m, 0);
        for (int i = 0; i < m; ++i) {
            auto iter = std::upper_bound(prefix.begin(), prefix.end(), people[i],
                                         [](int t, const auto& p) { return t < p.first; });
            if (iter != prefix.begin()) {
                result[i] = std::prev(iter)->second;
            }
        }
        return result;
    }
};
