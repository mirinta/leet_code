#include <array>
#include <vector>

/**
 * You are given a m x n matrix grid. Initially, you are located at the top-left corner (0, 0), and
 * in each step, you can only move right or down in the matrix.
 *
 * Among all possible paths starting from the top-left corner (0, 0) and ending in the bottom-right
 * corner (m - 1, n - 1), find the path with the maximum non-negative product. The product of a path
 * is the product of all integers in the grid cells visited along the path.
 *
 * Return the maximum non-negative product modulo 109 + 7. If the maximum product is negative,
 * return -1.
 *
 * Notice that the modulo is performed after getting the maximum product.
 *
 * ! m == grid.length
 * ! n == grid[i].length
 * ! 1 <= m, n <= 15
 * ! -4 <= grid[i][j] <= 4
 */

class Solution {
public:
    int maxProductPath(std::vector<std::vector<int>>& grid)
    {
        return approach2(grid);
    }

private:
    // DP with space optimization, TC = O(MN), SC = O(N)
    int approach2(const std::vector<std::vector<int>>& grid)
    {
        const int m = grid.size();
        const int n = grid[0].size();
        std::vector<std::array<long long, 2>> dp(n);
        dp[0] = {grid[0][0], grid[0][0]};
        for (int j = 1; j < n; ++j) {
            dp[j][0] = std::min(dp[j - 1][0] * grid[0][j], dp[j - 1][1] * grid[0][j]);
            dp[j][1] = std::max(dp[j - 1][0] * grid[0][j], dp[j - 1][1] * grid[0][j]);
        }
        for (int i = 1; i < m; ++i) {
            auto backup = dp[0][0];
            dp[0][0] = std::min(backup * grid[i][0], dp[0][1] * grid[i][0]);
            dp[0][1] = std::max(backup * grid[i][0], dp[0][1] * grid[i][0]);
            for (int j = 1; j < n; ++j) {
                backup = dp[j][0];
                dp[j][0] = std::min(
                    {backup * grid[i][j], dp[j][1] * grid[i][j], dp[j - 1][0] * grid[i][j], dp[j - 1][1] * grid[i][j]});
                dp[j][1] = std::max(
                    {backup * grid[i][j], dp[j][1] * grid[i][j], dp[j - 1][0] * grid[i][j], dp[j - 1][1] * grid[i][j]});
            }
        }
        if (dp[n - 1][1] < 0)
            return -1;

        return dp[n - 1][1] % kMod;
    }

    // DP, TC = O(MN), SC = O(MN)
    int approach1(const std::vector<std::vector<int>>& grid)
    {
        // dp[i][j][0] = min product moving from (0,0) to (i,j)
        // dp[i][j][1] = max product moving from (0,0) to (i,j)
        const int m = grid.size();
        const int n = grid[0].size();
        std::vector<std::vector<std::array<long long, 2>>> dp(
            m, std::vector<std::array<long long, 2>>(n, {INT_MAX, INT_MIN}));
        dp[0][0] = {grid[0][0], grid[0][0]};
        for (int i = 1; i < m; ++i) {
            dp[i][0][0] = std::min(dp[i - 1][0][0] * grid[i][0], dp[i - 1][0][1] * grid[i][0]);
            dp[i][0][1] = std::max(dp[i - 1][0][0] * grid[i][0], dp[i - 1][0][1] * grid[i][0]);
        }
        for (int j = 1; j < n; ++j) {
            dp[0][j][0] = std::min(dp[0][j - 1][0] * grid[0][j], dp[0][j - 1][1] * grid[0][j]);
            dp[0][j][1] = std::max(dp[0][j - 1][0] * grid[0][j], dp[0][j - 1][1] * grid[0][j]);
        }
        for (int i = 1; i < m; ++i) {
            for (int j = 1; j < n; ++j) {
                dp[i][j][0] = std::min({dp[i - 1][j][0] * grid[i][j], dp[i - 1][j][1] * grid[i][j],
                                        dp[i][j - 1][0] * grid[i][j], dp[i][j - 1][1] * grid[i][j]});
                dp[i][j][1] = std::max({dp[i - 1][j][0] * grid[i][j], dp[i - 1][j][1] * grid[i][j],
                                        dp[i][j - 1][0] * grid[i][j], dp[i][j - 1][1] * grid[i][j]});
            }
        }
        if (dp[m - 1][n - 1][1] < 0)
            return -1;

        return dp[m - 1][n - 1][1] % kMod;
    }

private:
    static constexpr int kMod = 1e9 + 7;
};