#include <algorithm>
#include <unordered_map>
#include <vector>

/**
 * A magician has various spells.
 *
 * You are given an array power, where each element represents the damage of a spell. Multiple
 * spells can have the same damage value.
 *
 * It is a known fact that if a magician decides to cast a spell with a damage of power[i], they
 * cannot cast any spell with a damage of power[i] - 2, power[i] - 1, power[i] + 1, or power[i] + 2.
 *
 * Each spell can be cast only once.
 *
 * Return the maximum possible total damage that a magician can cast.
 *
 * ! 1 <= power.length <= 10^5
 * ! 1 <= power[i] <= 10^9
 */

class Solution {
public:
    long long maximumTotalDamage(std::vector<int>& power)
    {
        std::unordered_map<int, long long> map;
        for (const auto& val : power) {
            map[val]++;
        }
        std::vector<long long> unique;
        unique.reserve(map.size());
        for (const auto& [val, freq] : map) {
            unique.push_back(val);
        }
        std::sort(unique.begin(), unique.end());
        const int n = unique.size();
        // dp[i] = max score of unique[0:i-1]
        std::vector<long long> dp(n + 1, 0);
        for (int i = 1; i <= n; ++i) {
            dp[i] = dp[i - 1]; // not picked
            const auto& val = unique[i - 1];
            auto iter = std::lower_bound(unique.begin(), unique.begin() + i, val - 2);
            if (iter != unique.end()) {
                dp[i] = std::max(dp[i], dp[iter - unique.begin()] + val * map[val]);
            } else {
                dp[i] = std::max(dp[i], val * map[val]);
            }
        }
        return dp[n];
    }
};