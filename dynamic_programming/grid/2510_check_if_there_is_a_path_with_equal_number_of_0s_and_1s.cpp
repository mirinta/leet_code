#include <vector>

/**
 * You are given a 0-indexed m x n binary matrix grid. You can move from a cell (row, col) to any of
 * the cells (row + 1, col) or (row, col + 1).
 *
 * Return true if there is a path from (0, 0) to (m - 1, n - 1) that visits an equal number of 0's
 * and 1's. Otherwise return false.
 *
 * ! m == grid.length
 * ! n == grid[i].length
 * ! 2 <= m, n <= 100
 * ! grid[i][j] is either 0 or 1.
 */

class Solution {
public:
    bool isThereAPath(std::vector<std::vector<int>>& grid)
    {
        const int m = grid.size();
        const int n = grid[0].size();
        if ((m + n - 1) % 2 != 0)
            return false;

        std::vector<std::vector<std::vector<int>>> memo(m,
                                                        std::vector<std::vector<int>>(n, std::vector<int>(m + n, -1)));
        const int target = (m + n - 1) / 2;
        return dfs(memo, 0, 0, 0, target, grid);
    }

private:
    bool dfs(std::vector<std::vector<std::vector<int>>>& memo,
             int i,
             int j,
             int count,
             int target,
             const std::vector<std::vector<int>>& grid)
    {
        const int m = grid.size();
        const int n = grid[0].size();
        if (i < 0 || i >= m || j < 0 || j >= n)
            return false;

        if (i == m - 1 && j == n - 1)
            return count == target;

        if (target - count > m + n - i - j - 1)
            return false;

        if (memo[i][j][count] != -1)
            return memo[i][j][count];

        if (dfs(memo, i + 1, j, count + grid[i][j], target, grid))
            return memo[i][j][count] = true;

        if (dfs(memo, i, j + 1, count + grid[i][j], target, grid))
            return memo[i][j][count] = true;

        return memo[i][j][count] = false;
    }
};