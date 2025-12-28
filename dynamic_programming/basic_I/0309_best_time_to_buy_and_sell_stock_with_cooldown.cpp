#include <array>
#include <vector>

/**
 * You are given an array prices where prices[i] is the price of a given stock on the ith day.
 *
 * Find the maximum profit you can achieve. You may complete as many transactions as you like (i.e.,
 * buy one and sell one share of the stock multiple times) with the following restrictions:
 *
 * - After you sell your stock, you cannot buy stock on the next day (i.e., cooldown one day).
 *
 * Note: You may not engage in multiple transactions simultaneously (i.e., you must sell the stock
 * before you buy again).
 *
 * ! 1 <= prices.length <= 5000
 * ! 0 <= prices[i] <= 1000
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
        int prevWithoutStock = 0;
        int withStock = -prices[0];
        int withoutStock = 0;
        for (int i = 2; i <= n; ++i) {
            const int backup = withoutStock;
            withoutStock = std::max(withoutStock, withStock + prices[i - 1]);
            withStock = std::max(withStock, prevWithoutStock - prices[i - 1]);
            prevWithoutStock = backup;
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
        // - dp[1][0] = 0
        // - dp[1][1] = -prices[0]
        std::vector<std::array<int, 2>> dp(1 + n, {0, 0});
        dp[0][1] = INT_MIN;
        dp[1][1] = -prices[0];
        for (int i = 2; i <= n; ++i) {
            dp[i][0] = std::max(dp[i - 1][0], dp[i - 1][1] + prices[i - 1]);
            dp[i][1] = std::max(dp[i - 1][1], dp[i - 2][0] - prices[i - 1]);
        }
        return dp[n][0];
    }
};
