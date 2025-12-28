#include <vector>

/**
 * You are given two 0-indexed integer arrays of the same length present and future where present[i]
 * is the current price of the ith stock and future[i] is the price of the ith stock a year in the
 * future. You may buy each stock at most once. You are also given an integer budget representing
 * the amount of money you currently have.
 *
 * Return the maximum amount of profit you can make.
 *
 * ! n == present.length == future.length
 * ! 1 <= n <= 1000
 * ! 0 <= present[i], future[i] <= 100
 * ! 0 <= budget <= 1000
 */

class Solution {
public:
    int maximumProfit(std::vector<int>& present, std::vector<int>& future, int budget)
    {
        return approach2(present, future, budget);
    }

private:
    int approach2(const std::vector<int>& present, const std::vector<int>& future, int budget)
    {
        const int n = present.size();
        std::vector<int> dp(budget + 1, 0);
        for (int i = 1; i <= n; ++i) {
            for (int j = budget; j >= 0; --j) {
                if (j - present[i - 1] >= 0) {
                    dp[j] = std::max(dp[j], dp[j - present[i - 1]] + future[i - 1] - present[i - 1]);
                }
            }
        }
        return dp[budget];
    }

    int approach1(const std::vector<int>& present, const std::vector<int>& future, int budget)
    {
        const int n = present.size();
        std::vector<std::vector<int>> dp(n + 1, std::vector<int>(budget + 1, 0));
        for (int i = 1; i <= n; ++i) {
            for (int j = 0; j <= budget; ++j) {
                dp[i][j] = dp[i - 1][j];
                if (j - present[i - 1] >= 0) {
                    dp[i][j] = std::max(dp[i][j], dp[i - 1][j - present[i - 1]] + future[i - 1] - present[i - 1]);
                }
            }
        }
        return dp[n][budget];
    }
};