#include <vector>

/**
 * You are given an integer array "coins" representing coins of different denominations and an
 * integer "amount" representing a total amount of money.
 *
 * Return the fewest number of coins that you need to make up the amount. If that amount of money
 * cannot be made up by any combination of the coins, return -1.
 *
 * You may assume that you have an infinite number of each kind of coin.
 *
 * ! 1 <= coins.length <= 12
 * ! 1 <= coins[i] <= 2^31 - 1
 * ! 0 <= amount <= 10^4
 */

class Solution
{
public:
    // time O(AN), space O(A)
    // - A is the amount, and N is the number of coins
    int coinChange(std::vector<int>& coins, int amount)
    {
        const int n = coins.size();
        // dp[i] = min number of coins to make up amount i
        std::vector<long> dp(amount + 1, INT_MAX);
        dp[0] = 0;
        for (int i = 1; i <= amount; ++i) {
            for (const auto& j : coins) {
                if (i >= j) {
                    dp[i] = std::min(dp[i], 1 + dp[i - j]);
                }
            }
        }
        return dp[amount] == INT_MAX ? -1 : dp[amount];
    }
};