#include <array>
#include <vector>

/**
 * You are given a 0-indexed m x n integer matrix grid and an integer k. You are currently at
 * position (0, 0) and you want to reach position (m - 1, n - 1) moving only down or right.
 *
 * Return the number of paths where the sum of the elements on the path is divisible by k. Since the
 * answer may be very large, return it modulo 10^9 + 7.
 *
 * ! m == grid.length
 * ! n == grid[i].length
 * ! 1 <= m, n <= 5 * 10^4
 * ! 1 <= m * n <= 5 * 10^4
 * ! 0 <= grid[i][j] <= 100
 * ! 1 <= k <= 50
 */

class Solution {
public:
    int numberOfPaths(std::vector<std::vector<int>>& grid, int k)
    {
        // dp[i][j][r] = num of paths moving from (0,0) to (i,j) with path sum % k = r
        constexpr int kMod = 1e9 + 7;
        const int m = grid.size();
        const int n = grid[0].size();
        std::vector<std::vector<std::vector<int>>> dp(m, std::vector<std::vector<int>>(n, std::vector<int>(k)));
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                const int x = grid[i][j] % k;
                if (i == 0 && j == 0) {
                    dp[0][0][x] = 1;
                    continue;
                }
                for (int r = 0; r < k; ++r) {
                    if (i - 1 >= 0) {
                        dp[i][j][r] = (dp[i][j][r] + dp[i - 1][j][(r - x + k) % k]) % kMod;
                    }
                    if (j - 1 >= 0) {
                        dp[i][j][r] = (dp[i][j][r] + dp[i][j - 1][(r - x + k) % k]) % kMod;
                    }
                }
            }
        }
        return dp[m - 1][n - 1][0];
    }
};
