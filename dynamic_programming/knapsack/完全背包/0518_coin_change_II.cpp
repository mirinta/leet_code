#include <vector>

/**
 * You are given an integer array "coins" representing coins of different denominations and an
 * integer "amount" representing a total amount of money.
 *
 * Return the number of combinations that make up that amount. If that amount of money cannot be
 * made up by any combination of the coins, return 0;
 *
 * You may assume that you have an infinite number of each kind of coin.
 *
 * The answer is guaranteed to fit into a signed 32-bit integer.
 *
 * ! 1 <= coins.length <= 300
 * ! 1 <= coins[i] <= 5000
 * ! All the values of coins are unique.
 * ! 0 <= amount <= 5000
 */

class Solution {
public:
    int change(int amount, std::vector<int>& coins)
    {
        return approach2(amount, coins);
    }

private:
    int approach2(int amount, const std::vector<int>& coins)
    {
        std::vector<int> dp(amount + 1, 0);
        dp[0] = 1;
        for (const auto& val : coins) {
            for (int j = 1; j <= amount; ++j) {
                if (j - val >= 0) {
                    dp[j] += dp[j - val];
                }
            }
        }
        return dp[amount];
    }

    int approach1(int amount, const std::vector<int>& coins)
    {
        // dp[i][j] = num of ways to make up j using coins[0:i-1]
        const int n = coins.size();
        std::vector<std::vector<int>> dp(n + 1, std::vector<int>(amount + 1, 0));
        for (int i = 0; i <= n; ++i) {
            dp[i][0] = 1;
        }
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= amount; ++j) {
                dp[i][j] = dp[i - 1][j];
                if (j - coins[i - 1] >= 0) {
                    dp[i][j] += dp[i][j - coins[i - 1]];
                }
            }
        }
        return dp[n][amount];
    }
};