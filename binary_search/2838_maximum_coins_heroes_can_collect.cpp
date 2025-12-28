#include <algorithm>
#include <vector>

/**
 * There is a battle and n heroes are trying to defeat m monsters. You are given two 1-indexed
 * arrays of positive integers heroes and monsters of length n and m, respectively. heroes[i] is the
 * power of ith hero, and monsters[i] is the power of ith monster.
 *
 * The ith hero can defeat the jth monster if monsters[j] <= heroes[i].
 *
 * You are also given a 1-indexed array coins of length m consisting of positive integers. coins[i]
 * is the number of coins that each hero earns after defeating the ith monster.
 *
 * Return an array ans of length n where ans[i] is the maximum number of coins that the ith hero can
 * collect from this battle.
 *
 * Notes
 *
 * - The health of a hero doesn't get reduced after defeating a monster.
 *
 * - Multiple heroes can defeat a monster, but each monster can be defeated by a given hero only
 * once.
 *
 * ! 1 <= n == heroes.length <= 10^5
 * ! 1 <= m == monsters.length <= 10^5
 * ! coins.length == m
 * ! 1 <= heroes[i], monsters[i], coins[i] <= 10^9
 */

class Solution {
public:
    std::vector<long long> maximumCoins(std::vector<int>& heroes, std::vector<int>& monsters, std::vector<int>& coins)
    {
        const int m = monsters.size();
        std::vector<std::pair<int, int>> info;
        info.reserve(m);
        for (int i = 0; i < m; ++i) {
            info.emplace_back(monsters[i], coins[i]);
        }
        std::sort(info.begin(), info.end(), [](const auto& p1, const auto& p2) { return p1.first < p2.first; });
        std::vector<long long> presum(m + 1);
        for (int i = 1; i <= m; ++i) {
            presum[i] = presum[i - 1] + info[i - 1].second;
        }
        const int n = heroes.size();
        std::vector<long long> result(n);
        for (int i = 0; i < n; ++i) {
            auto iter = std::upper_bound(info.begin(), info.end(), heroes[i],
                                         [](int val, const auto& p) { return p.first > val; });
            result[i] = presum[iter - info.begin()];
        }
        return result;
    }
};