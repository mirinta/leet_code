#include <vector>

/**
 * 在一个 m*n 的棋盘的每一格都放有一个礼物，每个礼物都有一定的价值（价值大于0）。
 *
 * 你可以从棋盘的左上角开始拿格子里的礼物，并每次向右或者向下移动一格、直到到达棋盘的右下角。
 *
 * 给定一个棋盘及其上面的礼物的价值，请计算你最多能拿到多少价值的礼物？
 *
 * ! 0 < grid.length <= 200
 * ! 0 < grid[0].length <= 200
 */

class Solution {
public:
    int maxValue(std::vector<std::vector<int>>& grid)
    {
        return approach2(grid);
    }

private:
    int approach2(std::vector<std::vector<int>>& grid)
    {
        // DP with space optimization (remove the first dimension)
        if (grid.empty() || grid[0].empty())
            return 0;

        const int m = grid.size();
        const int n = grid[0].size();
        std::vector<int> dp(n + 1, 0);
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                dp[j] = grid[i - 1][j - 1] + std::max(dp[j], dp[j - 1]);
            }
        }
        return dp[n];
    }

    int approach1(std::vector<std::vector<int>>& grid)
    {
        if (grid.empty() || grid[0].empty())
            return 0;

        // dp[i][j] = max value gathering from (0,0) to (i-1,j-1)
        const int m = grid.size();
        const int n = grid[0].size();
        std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1, 0));
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                dp[i][j] = grid[i - 1][j - 1] + std::max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
        return dp[m][n];
    }
};