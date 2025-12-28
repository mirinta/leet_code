#include <vector>

/**
 * You are given an n x n grid representing a field of cherries, each cell is one of three possible
 * integers.
 *
 * - 0 means the cell is empty, so you can pass through,
 *
 * - 1 means the cell contains a cherry that you can pick up and pass through, or
 *
 * - -1 means the cell contains a thorn that blocks your way.
 *
 * Return the maximum number of cherries you can collect by following the rules below:
 *
 * - Starting at the position (0, 0) and reaching (n - 1, n - 1) by moving right or down through
 * valid path cells (cells with value 0 or 1).
 *
 * - After reaching (n - 1, n - 1), returning to (0, 0) by moving left or up through valid path
 * cells. When passing through a path cell containing a cherry, you pick it up, and the cell becomes
 * an empty cell 0.
 *
 * - If there is no valid path between (0, 0) and (n - 1, n - 1), then no cherries can be collected.
 *
 * ! n == grid.length
 * ! n == grid[i].length
 * ! 1 <= n <= 50
 * ! grid[i][j] is -1, 0, or 1.
 * ! grid[0][0] != -1
 * ! grid[n - 1][n - 1] != -1
 */

class Solution {
public:
    int cherryPickup(std::vector<std::vector<int>>& grid)
    {
        return approach2(grid);
    }

private:
    int approach2(const std::vector<std::vector<int>>& grid)
    {
        // moving the same num of steps,
        // person A is located at (i,j) and peron B is located at (p,q),
        // i + j = p + q
        const int n = grid.size();
        int dp[50][50][50];
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                for (int p = 0; p < n; ++p) {
                    dp[i][j][p] = INT_MIN;
                }
            }
        }
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == -1)
                    continue;

                for (int p = 0; p < n; ++p) {
                    const int q = i + j - p;
                    if (q < 0 || q >= n || grid[p][q] == -1)
                        continue;

                    if (i == 0 && j == 0 && p == 0 && q == 0) {
                        dp[i][j][p] = 0;
                    }
                    if (i - 1 >= 0 && p - 1 >= 0 && dp[i - 1][j][p - 1] != INT_MIN) {
                        dp[i][j][p] = std::max(dp[i][j][p], dp[i - 1][j][p - 1]);
                    }
                    if (i - 1 >= 0 && q - 1 >= 0 && dp[i - 1][j][p] != INT_MIN) {
                        dp[i][j][p] = std::max(dp[i][j][p], dp[i - 1][j][p]);
                    }
                    if (j - 1 >= 0 && p - 1 >= 0 && dp[i][j - 1][p - 1] != INT_MIN) {
                        dp[i][j][p] = std::max(dp[i][j][p], dp[i][j - 1][p - 1]);
                    }
                    if (j - 1 >= 0 && q - 1 >= 0 && dp[i][j - 1][p] != INT_MIN) {
                        dp[i][j][p] = std::max(dp[i][j][p], dp[i][j - 1][p]);
                    }
                    if (dp[i][j][p] == INT_MIN)
                        continue;

                    if (i != p && j != q) {
                        dp[i][j][p] += grid[i][j] + grid[p][q];
                    } else {
                        dp[i][j][p] += grid[i][j];
                    }
                }
            }
        }
        return std::max(0, dp[n - 1][n - 1][n - 1]);
    }

    int approach1(const std::vector<std::vector<int>>& grid)
    {
        // dp[i][j][p][q] = max score of person A and person B moving from (0,0) to (i,j)
        // simultaneously
        const int n = grid.size();
        int dp[50][50][50][50];
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                for (int p = 0; p < n; ++p) {
                    for (int q = 0; q < n; ++q) {
                        dp[i][j][p][q] = INT_MIN;
                    }
                }
            }
        }
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == -1)
                    continue;

                for (int p = 0; p < n; ++p) {
                    for (int q = 0; q < n; ++q) {
                        if (grid[p][q] == -1)
                            continue;

                        if (i == 0 && j == 0 && p == 0 && q == 0) {
                            dp[i][j][p][q] = 0;
                        }
                        if (i - 1 >= 0 && p - 1 >= 0 && dp[i - 1][j][p - 1][q] != INT_MIN) {
                            dp[i][j][p][q] = std::max(dp[i][j][p][q], dp[i - 1][j][p - 1][q]);
                        }
                        if (i - 1 >= 0 && q - 1 >= 0 && dp[i - 1][j][p][q - 1] != INT_MIN) {
                            dp[i][j][p][q] = std::max(dp[i][j][p][q], dp[i - 1][j][p][q - 1]);
                        }
                        if (j - 1 >= 0 && p - 1 >= 0 && dp[i][j - 1][p - 1][q] != INT_MIN) {
                            dp[i][j][p][q] = std::max(dp[i][j][p][q], dp[i][j - 1][p - 1][q]);
                        }
                        if (j - 1 >= 0 && q - 1 >= 0 && dp[i][j - 1][p][q - 1] != INT_MIN) {
                            dp[i][j][p][q] = std::max(dp[i][j][p][q], dp[i][j - 1][p][q - 1]);
                        }
                        if (dp[i][j][p][q] == INT_MIN)
                            continue;

                        if (i != p && j != q) {
                            dp[i][j][p][q] += grid[i][j] + grid[p][q];
                        } else {
                            dp[i][j][p][q] += grid[i][j];
                        }
                    }
                }
            }
        }
        return std::max(0, dp[n - 1][n - 1][n - 1][n - 1]);
    }
};