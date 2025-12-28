#include <array>
#include <vector>

/**
 * You are given an array prices where prices[i] is the price of a given stock on the ith day, and
 * an integer fee representing a transaction fee.
 *
 * Find the maximum profit you can achieve. You may complete as many transactions as you like, but
 * you need to pay the transaction fee for each transaction.
 *
 * Note: You may not engage in multiple transactions simultaneously (i.e., you must sell the stock
 * before you buy again).
 *
 * ! 1 <= prices.length <= 5 * 10^4
 * ! 1 <= prices[i] < 5 * 10^4
 * ! 0 <= fee < 5 * 10^4
 */

class Solution {
public:
    int maxProfit(std::vector<int>& prices, int fee)
    {
        return approach2(prices, fee);
    }

private:
    // DP with space optimization
    int approach2(const std::vector<int>& prices, int fee)
    {
        const int n = prices.size();
        int withStock = INT_MIN / 2;
        int withoutStock = 0;
        for (int i = 1; i <= n; ++i) {
            const int backup = withoutStock;
            withoutStock = std::max(withoutStock, withStock + prices[i - 1] - fee);
            withStock = std::max(withStock, backup - prices[i - 1]);
        }
        return withoutStock;
    }

    // DP
    int approach1(const std::vector<int>& prices, int fee)
    {
        const int n = prices.size();
        // dp[i][0] = max profit at the end of the ith day without holding any stock
        // dp[i][1] = max profit at the end of the ith day holding one stock
        // base cases:
        // - dp[0][0] = 0
        // - dp[0][1] = INT_MIN/2
        std::vector<std::array<int, 2>> dp(1 + n, {0, 0});
        dp[0][1] = INT_MIN / 2;
        for (int i = 1; i <= n; ++i) {
            dp[i][0] = std::max(dp[i - 1][0], dp[i - 1][1] + prices[i - 1] - fee);
            dp[i][1] = std::max(dp[i - 1][1], dp[i - 1][0] - prices[i - 1]);
        }
        return dp[n][0];
    }
};
