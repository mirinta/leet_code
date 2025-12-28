#include <vector>

/**
 * There is a robot on an "m x n" grid. The robot is initially located at the top-left corner (i.e.,
 * grid[0][0]). The robot tries to move to the bottom-right corner (i.e., grid[m - 1][n - 1]). The
 * robot can only move either down or right at any point in time.
 *
 * Given the two integers m and n, return the number of possible unique paths that the robot can
 * take to reach the bottom-right corner.
 *
 * The test cases are generated so that the answer will be less than or equal to 2 * 10^9.
 *
 * ! 1 <= m, n <= 100
 */

class Solution {
public:
    int uniquePaths(int m, int n)
    {
        return approach2(m, n);
    }

private:
    // DP with space optimization, time O(MN), space O(N)
    int approach2(int m, int n)
    {
        std::vector<int> dp(n, 1);
        for (int i = 1; i < m; ++i) {
            dp[0] = 1;
            for (int j = 1; j < n; ++j) {
                dp[j] += dp[j - 1];
            }
        }
        return dp[n - 1];
    }

    // DP, time O(MN), space O(MN)
    int approach1(int m, int n)
    {
        // dp[i][j] = num of unique paths that the robot can take to reach (i,j)
        // base cases:
        // - dp[0][0] = 1
        // - dp[i][0] = 1
        // - dp[0][j] = 1
        std::vector<std::vector<int>> dp(m, std::vector<int>(n, 0));
        for (int i = 0; i < m; ++i) {
            dp[i][0] = 1;
        }
        for (int j = 0; j < n; ++j) {
            dp[0][j] = 1;
        }
        for (int i = 1; i < m; ++i) {
            for (int j = 1; j < n; ++j) {
                dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
            }
        }
        return dp[m - 1][n - 1];
    }
};