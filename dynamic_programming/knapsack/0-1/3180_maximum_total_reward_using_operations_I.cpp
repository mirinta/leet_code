#include <algorithm>
#include <vector>

/**
 * You are given an integer array rewardValues of length n, representing the values of rewards.
 *
 * Initially, your total reward x is 0, and all indices are unmarked. You are allowed to perform the
 * following operation any number of times:
 *
 * - Choose an unmarked index i from the range [0, n - 1].
 *
 * - If rewardValues[i] is greater than your current total reward x, then add rewardValues[i] to x
 * (i.e., x = x + rewardValues[i]), and mark the index i.
 *
 * Return an integer denoting the maximum total reward you can collect by performing the operations
 * optimally.
 *
 * ! 1 <= rewardValues.length <= 2000
 * ! 1 <= rewardValues[i] <= 2000
 */

class Solution {
public:
    int maxTotalReward(std::vector<int>& rewardValues)
    {
        return approach2(rewardValues);
    }

private:
    // DP with space optimization, TC = O(n*max), SC = O(max)
    int approach2(std::vector<int>& rewardValues)
    {
        std::sort(rewardValues.begin(), rewardValues.end());
        auto iter = std::unique(rewardValues.begin(), rewardValues.end());
        rewardValues.erase(iter, rewardValues.end());
        const auto& max = rewardValues.back();
        std::vector<bool> dp(2 * max, false);
        dp[0] = true;
        for (const auto& val : rewardValues) {
            for (int j = 2 * max - 1; j >= 0; --j) {
                const bool case1 = dp[j];
                const bool case2 = j - val >= 0 && val > j - val && dp[j - val];
                dp[j] = case1 || case2;
            }
        }
        for (int j = 2 * max - 1; j >= 0; --j) {
            if (dp[j])
                return j;
        }
        return -1;
    }

    // DP, TC = O(n*max), SC = O(n*max)
    int approach1(std::vector<int>& rewardValues)
    {
        // duplicate values are useless
        std::sort(rewardValues.begin(), rewardValues.end());
        auto iter = std::unique(rewardValues.begin(), rewardValues.end());
        rewardValues.erase(iter, rewardValues.end());
        const int n = rewardValues.size();
        // dp[i][j] = whether it is possible to make up j using rewardValues[0:i-1]
        const auto& max = rewardValues.back();
        // if we pick the max element, then x satisfies x < max
        // thus, the maximum score = x + max < 2 * max
        std::vector<std::vector<bool>> dp(n + 1, std::vector<bool>(2 * max, false));
        for (int i = 0; i <= n; ++i) {
            dp[i][0] = true;
        }
        for (int i = 1; i <= n; ++i) {
            const auto& val = rewardValues[i - 1];
            for (int j = 1; j < 2 * max; ++j) {
                // case 1: current value is not picked
                const bool case1 = dp[i - 1][j];
                // case 2: current value is picked
                const bool case2 = j - val >= 0 && val > j - val && dp[i - 1][j - val];
                dp[i][j] = case1 || case2;
            }
        }
        for (int j = 2 * max - 1; j >= 0; --j) {
            if (dp[n][j])
                return j;
        }
        return -1;
    }
};