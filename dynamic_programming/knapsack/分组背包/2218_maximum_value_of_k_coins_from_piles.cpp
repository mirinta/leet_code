#include <vector>

/**
 * There are n piles of coins on a table. Each pile consists of a positive number of coins of
 * assorted denominations.
 *
 * In one move, you can choose any coin on top of any pile, remove it, and add it to your wallet.
 *
 * Given a list piles, where piles[i] is a list of integers denoting the composition of the ith pile
 * from top to bottom, and a positive integer k, return the maximum total value of coins you can
 * have in your wallet if you choose exactly k coins optimally.
 *
 * ! n == piles.length
 * ! 1 <= n <= 1000
 * ! 1 <= piles[i][j] <= 10^5
 * ! 1 <= k <= sum(piles[i].length) <= 2000
 */

class Solution {
public:
    int maxValueOfCoins(std::vector<std::vector<int>>& piles, int k)
    {
        // dp[i][j] = max value we can achieve by choosing exactly j coins from piles[0:i-1]
        const int n = piles.size();
        std::vector<std::vector<int>> presum;
        presum.reserve(n);
        for (const auto& pile : piles) {
            std::vector<int> sum(pile.size() + 1, 0);
            for (int i = 1; i <= pile.size(); ++i) {
                sum[i] = sum[i - 1] + pile[i - 1];
            }
            presum.push_back(std::move(sum));
        }
        std::vector<std::vector<int>> dp(n + 1, std::vector<int>(k + 1, 0));
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= k; ++j) {
                // choose t coins from piles[i-1]
                for (int t = 0; t <= std::min<int>(j, piles[i - 1].size()); ++t) {
                    dp[i][j] = std::max(dp[i][j], dp[i - 1][j - t] + presum[i - 1][t]);
                }
            }
        }
        return dp[n][k];
    }
};