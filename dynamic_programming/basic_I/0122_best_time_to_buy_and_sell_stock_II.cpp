#include <vector>

/**
 * You are given an integer array prices where prices[i] is the price of a given stock on the ith
 * day.
 *
 * On each day, you may decide to buy and/or sell the stock. You can only hold at most one share of
 * the stock at any time. However, you can buy it then immediately sell it on the same day.
 *
 * Find and return the maximum profit you can achieve.
 *
 * ! 1 <= prices.length <= 3 * 10^4
 * ! 0 <= prices[i] <= 10^4
 */

class Solution {
public:
    int maxProfit(std::vector<int>& prices)
    {
        return approach2(prices);
    }

private:
    // DP with space optimization
    int approach2(const std::vector<int>& prices)
    {
        const int n = prices.size();
        int withoutStock = 0;
        int withStock = INT_MIN;
        for (int i = 1; i <= n; ++i) {
            const int backup = withStock;
            withStock = std::max(withStock, withoutStock - prices[i - 1]);
            withoutStock = std::max(withoutStock, backup + prices[i - 1]);
        }
        return withoutStock;
    }

    // DP
    int approach1(const std::vector<int>& prices)
    {
        const int n = prices.size();
        // dp[i][0] = max profit at the end of the ith day without holding any stock
        // dp[i][1] = max profit at the end of the ith day holding one stock
        // base cases:
        // - dp[0][0] = 0
        // - dp[0][1] = INT_MIN
        std::vector<std::vector<int>> dp(1 + n, std::vector<int>(2, 0));
        dp[0][1] = INT_MIN;
        for (int i = 1; i <= n; ++i) {
            dp[i][0] = std::max(dp[i - 1][0], dp[i - 1][1] + prices[i - 1]);
            dp[i][1] = std::max(dp[i - 1][1], dp[i - 1][0] - prices[i - 1]);
        }
        return dp[n][0];
    }
};
