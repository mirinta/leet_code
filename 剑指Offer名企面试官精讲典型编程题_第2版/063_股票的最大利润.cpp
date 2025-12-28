#include <vector>

/**
 * 假设把某股票的价格按照时间先后顺序存储在数组中，请问买卖该股票一次可能获得的最大利润是多少？
 *
 * ! 0 <= 数组长度 <= 10^5
 *
 * ! 本题与LC 121相同。
 */

class Solution {
public:
    int maxProfit(std::vector<int>& prices)
    {
        // DP with space optimization
        int withStock = INT_MIN;
        int witoutStock = 0;
        for (const auto& price : prices) {
            witoutStock = std::max(witoutStock, withStock + price);
            withStock = std::max(withStock, -price);
        }
        return witoutStock;
    }

private:
    int approach1(std::vector<int>& prices)
    {
        // only buy one stock
        // dp[i][0] = max profit at the end of the ith day, without any stock in-hand
        // dp[i][1] = max profit at the end of the ith day, with one stock in-hand
        const int n = prices.size();
        std::vector<std::vector<int>> dp(n + 1, std::vector<int>(2, 0));
        dp[0][1] = INT_MIN;
        for (int i = 1; i <= n; ++i) {
            dp[i][0] = std::max(dp[i - 1][0], dp[i - 1][1] + prices[i - 1]);
            dp[i][1] = std::max(dp[i - 1][1], -prices[i - 1]);
        }
        return dp[n][0];
    }
};
