#include <vector>

/**
 * You are given an m x n matrix grid consisting of positive integers. You can move from a cell in
 * the matrix to any other cell that is either to the bottom or to the right (not necessarily
 * adjacent). The score of a move from a cell with the value c1 to a cell with the value c2 is c2 -
 * c1.
 *
 * You can start at any cell, and you have to make at least one move.
 *
 * Return the maximum total score you can achieve.
 *
 * ! m == grid.length
 * ! n == grid[i].length
 * ! 2 <= m, n <= 1000
 * ! 4 <= m * n <= 10^5
 * ! 1 <= grid[i][j] <= 10^5
 */

class Solution {
public:
    int maxScore(std::vector<std::vector<int>>& grid)
    {
        // score of any path from c1 to ck = c2-c1 + c3-c2 + ... + ck-c_k-1 = ck-c1
        // given an ending point (i,j), we need to find a starting point (x,y)
        // such that (x,y) is in the top-left area of (i,j) and
        // grid[i][j] - grid[x][y] is maximized => grid[x][y] is minimized
        const int m = grid.size();
        const int n = grid[0].size();
        // dp[i][j] = min element of grid[0:i][0:j]
        // dp[i][j] = std::min(grid[i][j], dp[i-1][j], dp[i][j-1])
        // for each ending point (i,j), since we have to make at least one move,
        // score of ending at (i,j) = grid[i][j] - std::min(dp[i-1][j], dp[i][j-1])
        std::vector<std::vector<int>> dp(m, std::vector<int>(n, INT_MAX));
        int result = INT_MIN;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i == 0 && j == 0) {
                    dp[0][0] = grid[0][0];
                    continue;
                }
                dp[i][j] = std::min(dp[i][j], grid[i][j]);
                if (i - 1 >= 0) {
                    result = std::max(result, grid[i][j] - dp[i - 1][j]);
                    dp[i][j] = std::min(dp[i][j], dp[i - 1][j]);
                }
                if (j - 1 >= 0) {
                    result = std::max(result, grid[i][j] - dp[i][j - 1]);
                    dp[i][j] = std::min(dp[i][j], dp[i][j - 1]);
                }
            }
        }
        return result;
    }
};