#include <algorithm>
#include <array>
#include <vector>

/**
 * You are given an m x n grid. A robot starts at the top-left corner of the grid (0, 0) and wants
 * to reach the bottom-right corner (m - 1, n - 1). The robot can move either right or down at any
 * point in time.
 *
 * The grid contains a value coins[i][j] in each cell:
 *
 * - If coins[i][j] >= 0, the robot gains that many coins.
 *
 * - If coins[i][j] < 0, the robot encounters a robber, and the robber steals the absolute value of
 * coins[i][j] coins.
 *
 * The robot has a special ability to neutralize robbers in at most 2 cells on its path, preventing
 * them from stealing coins in those cells.
 *
 * Note: The robot's total coins can be negative.
 *
 * Return the maximum profit the robot can gain on the route.
 *
 * ! m == coins.length
 * ! n == coins[i].length
 * ! 1 <= m, n <= 500
 * ! -1000 <= coins[i][j] <= 1000
 */

class Solution {
public:
    int maximumAmount(std::vector<std::vector<int>>& coins)
    {
        const int m = coins.size();
        const int n = coins[0].size();
        std::vector<std::vector<std::array<long long, 3>>> dp(
            m, std::vector<std::array<long long, 3>>(n, {INT_MIN, INT_MIN, INT_MIN}));
        dp[0][0][0] = coins[0][0];
        if (coins[0][0] < 0) {
            dp[0][0][1] = 0;
        }
        for (int j = 1; j < n; ++j) {
            for (int k = 0; k < 3; ++k) {
                dp[0][j][k] = coins[0][j] + dp[0][j - 1][k];
                if (coins[0][j] < 0 && k > 0) {
                    dp[0][j][k] = std::max(dp[0][j][k], dp[0][j - 1][k - 1]);
                }
            }
        }
        for (int i = 1; i < m; ++i) {
            for (int k = 0; k < 3; ++k) {
                dp[i][0][k] = coins[i][0] + dp[i - 1][0][k];
                if (coins[i][0] < 0 && k > 0) {
                    dp[i][0][k] = std::max(dp[i][0][k], dp[i - 1][0][k - 1]);
                }
            }
        }
        for (int i = 1; i < m; ++i) {
            for (int j = 1; j < n; ++j) {
                for (int k = 0; k < 3; ++k) {
                    dp[i][j][k] = std::max(dp[i - 1][j][k], dp[i][j - 1][k]) + coins[i][j];
                    if (coins[i][j] < 0 && k > 0) {
                        dp[i][j][k] = std::max({dp[i][j][k], dp[i - 1][j][k - 1], dp[i][j - 1][k - 1]});
                    }
                }
            }
        }
        return *std::max_element(dp[m - 1][n - 1].begin(), dp[m - 1][n - 1].end());
    }
};