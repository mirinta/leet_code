#include <algorithm>
#include <array>
#include <vector>

/**
 * You are given a 2D matrix grid of size m x n. In one operation, you can change the value of any
 * cell to any non-negative number. You need to perform some operations such that each cell
 * grid[i][j] is:
 *
 * - Equal to the cell below it, i.e. grid[i][j] == grid[i + 1][j] (if it exists).
 *
 * - Different from the cell to its right, i.e. grid[i][j] != grid[i][j + 1] (if it exists).
 *
 * Return the minimum number of operations needed.
 *
 * ! 1 <= n, m <= 1000
 * ! 0 <= grid[i][j] <= 9
 */

class Solution {
public:
    int minimumOperations(std::vector<std::vector<int>>& grid)
    {
        return approach2(grid);
    }

private:
    int approach2(const std::vector<std::vector<int>>& grid)
    {
        const int m = grid.size();
        const int n = grid[0].size();
        std::vector<std::vector<int>> count(n, std::vector<int>(11, 0));
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                count[j][grid[i][j]]++;
            }
        }
        // dp[j][k] = min operations to make grid[:][0:j] valid while grid[0][j] = k
        std::vector<std::array<int, 10>> dp(n);
        for (int k = 0; k < 10; ++k) {
            dp[0][k] = m - count[0][k];
        }
        for (int j = 1; j < n; ++j) {
            std::fill(dp[j].begin(), dp[j].end(), INT_MAX);
            for (int k = 0; k < 10; ++k) {
                for (int prev = 0; prev < 10; ++prev) {
                    if (prev == k)
                        continue;

                    dp[j][k] = std::min(dp[j][k], dp[j - 1][prev] + m - count[j][k]);
                }
            }
        }
        return *std::min_element(dp[n - 1].begin(), dp[n - 1].end());
    }

    int approach1(const std::vector<std::vector<int>>& grid)
    {
        const int m = grid.size();
        const int n = grid[0].size();
        std::vector<std::vector<int>> count(n, std::vector<int>(11, 0)); // frequency of each element of grid[:][j]
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                count[j][grid[i][j]]++;
            }
        }
        std::vector<std::vector<int>> memo(n, std::vector<int>(11, -1));
        return dfs(memo, 0, 10, m, n, count);
    }

    // min operations to make grid[:][col:n-1] valid
    int dfs(std::vector<std::vector<int>>& memo,
            int col,
            int prev,
            int m,
            int n,
            const std::vector<std::vector<int>>& count)
    {
        if (col == n)
            return 0;

        if (memo[col][prev] != -1)
            return memo[col][prev];

        int result = INT_MAX;
        for (int top = 0; top < 10; ++top) {
            if (prev == top)
                continue;

            result = std::min(result, m - count[col][top] + dfs(memo, col + 1, top, m, n, count));
        }
        return memo[col][prev] = result;
    }
};