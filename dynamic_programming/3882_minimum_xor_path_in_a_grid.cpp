#include <array>
#include <vector>

/**
 * You are given a 2D integer array grid of size m * n.
 *
 * You start at the top-left cell (0, 0) and want to reach the bottom-right cell (m - 1, n - 1).
 *
 * At each step, you may move either right or down.
 *
 * The cost of a path is defined as the bitwise XOR of all the values in the cells along that path, including the start
 * and end cells.
 *
 * Return the minimum possible XOR value among all valid paths from (0, 0) to (m - 1, n - 1).
 *
 * ! 1 <= m == grid.length <= 1000
 * ! 1 <= n == grid[i].length <= 1000
 * ! m * n <= 1000
 * ! 0 <= grid[i][j] <= 1023​
 */

class Solution {
public:
    int minCost(std::vector<std::vector<int>>& grid)
    {
        // dp[i][j][k] = whether it is reachable from (0,0) to (i,j) with score k
        const int m = grid.size();
        const int n = grid[0].size();
        std::vector dp(m, std::vector<std::array<bool, 1024>>(n));
        dp[0][0][grid[0][0]] = true;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i == 0 && j == 0)
                    continue;

                const auto& val = grid[i][j];
                for (int k = 0; k < 1024; ++k) {
                    if (i > 0) {
                        dp[i][j][k] |= dp[i - 1][j][k ^ val];
                    }
                    if (j > 0) {
                        dp[i][j][k] |= dp[i][j - 1][k ^ val];
                    }
                }
            }
        }
        for (int k = 0; k < 1024; ++k) {
            if (dp[m - 1][n - 1][k])
                return k;
        }
        return -1;
    }
};
