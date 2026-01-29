#include <vector>

/**
 * You are given a m x n 2D integer array grid and an integer k. You start at the top-left cell (0, 0) and your goal is
 * to reach the bottom‐right cell (m - 1, n - 1).
 *
 * There are two types of moves available:
 *
 * - Normal move: You can move right or down from your current cell (i, j), i.e. you can move to (i, j + 1) (right) or
 * (i + 1, j) (down). The cost is the value of the destination cell.
 *
 * - Teleportation: You can teleport from any cell (i, j), to any cell (x, y) such that grid[x][y] <= grid[i][j]; the
 * cost of this move is 0. You may teleport at most k times.
 *
 * Return the minimum total cost to reach cell (m - 1, n - 1) from (0, 0).
 *
 * ! 2 <= m, n <= 80
 * ! m == grid.length
 * ! n == grid[i].length
 * ! 0 <= grid[i][j] <= 10^4
 * ! 0 <= k <= 10
 */

class Solution {
public:
    int minCost(std::vector<std::vector<int>>& grid, int k)
    {
        // dp[t][i][j] = min cost to reach (i-1,j-1) from (0,0) using at most t teleportations
        // note: including grid[0][0]
        const int m = grid.size();
        const int n = grid[0].size();
        int max = INT_MIN;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                max = std::max(max, grid[i][j]);
            }
        }
        std::vector<std::vector<int>> suffixMin(k + 1, std::vector<int>(max + 1, INT_MAX));
        std::vector<std::vector<std::vector<int>>> dp(k + 1,
                                                      std::vector<std::vector<int>>(m, std::vector<int>(n, INT_MAX)));
        int result = INT_MAX;
        for (int t = 0; t <= k; ++t) {
            for (int i = 0; i < m; ++i) {
                for (int j = 0; j < n; ++j) {
                    const auto& val = grid[i][j];
                    if (i == 0 && j == 0) {
                        dp[t][i][j] = val;
                    } else if (i == 0) {
                        dp[t][i][j] = val + dp[t][i][j - 1];
                    } else if (j == 0) {
                        dp[t][i][j] = val + dp[t][i - 1][j];
                    } else {
                        dp[t][i][j] = val + std::min(dp[t][i - 1][j], dp[t][i][j - 1]);
                    }
                    if (t > 0) {
                        dp[t][i][j] = std::min(dp[t][i][j], suffixMin[t - 1][val]);
                    }
                    suffixMin[t][val] = std::min(suffixMin[t][val], dp[t][i][j]);
                }
            }
            for (int p = max - 1; p >= 0; --p) {
                suffixMin[t][p] = std::min(suffixMin[t][p], suffixMin[t][p + 1]);
            }
            result = std::min(result, dp[t][m - 1][n - 1] - grid[0][0]);
        }
        return result;
    }
};