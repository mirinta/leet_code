#include <vector>

/**
 * You are given an "m x n" integer array "grid". There is a robot initially located at the top-left
 * corner (i.e., grid[0][0]). The robot tries to move to the bottom-right corner (i.e., grid[m -
 * 1][n - 1]). The robot can only move either down or right at any point in time.
 *
 * An obstacle and space are marked as 1 or 0 respectively in grid. A path that the robot takes
 * cannot include any square that is an obstacle.
 *
 * Return the number of possible unique paths that the robot can take to reach the bottom-right
 * corner.
 *
 * The text cases are generated so that the answer will be less than or equal to 2 * 10^9.
 *
 * ! m == obstacleGrid.length
 * ! n == obstacleGrid[i].length
 * ! 1 <= m, n <= 100
 * ! obstacleGrid[i][j] is 0 or 1.
 */

class Solution {
public:
    int uniquePathsWithObstacles(std::vector<std::vector<int>>& obstacleGrid)
    {
        return approach2(obstacleGrid);
    }

private:
    // DP with space optimization, TC = O(MN), SC = O(MN)
    int approach2(const std::vector<std::vector<int>>& grid)
    {
        const int m = grid.size();
        const int n = grid[0].size();
        if (grid[0][0] == 1 || grid[m - 1][n - 1] == 1)
            return 0;

        std::vector<int> dp(n);
        dp[0] = 1;
        for (int j = 1; j < n; ++j) {
            dp[j] = grid[0][j] == 0 && dp[j - 1];
        }
        for (int i = 1; i < m; ++i) {
            dp[0] = grid[i][0] == 0 && dp[0];
            for (int j = 1; j < n; ++j) {
                if (grid[i][j] == 1) {
                    dp[j] = 0;
                } else {
                    dp[j] = dp[j] + dp[j - 1];
                }
            }
        }
        return dp[n - 1];
    }

    // DP, TC = O(MN), SC = O(MN)
    int approach1(const std::vector<std::vector<int>>& grid)
    {
        const int m = grid.size();
        const int n = grid[0].size();
        if (grid[0][0] == 1 || grid[m - 1][n - 1] == 1)
            return 0;

        // dp[i][j] = num of unique paths moving from (0,0) to (i,j)
        std::vector<std::vector<int>> dp(m, std::vector<int>(n));
        dp[0][0] = 1;
        for (int i = 1; i < m; ++i) {
            dp[i][0] = grid[i][0] == 0 && dp[i - 1][0];
        }
        for (int j = 1; j < n; ++j) {
            dp[0][j] = grid[0][j] == 0 && dp[0][j - 1];
        }
        for (int i = 1; i < m; ++i) {
            for (int j = 1; j < n; ++j) {
                if (grid[i][j] == 1) {
                    dp[i][j] = 0;
                } else {
                    dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
                }
            }
        }
        return dp[m - 1][n - 1];
    }
};