#include <vector>

/**
 * You are given an m x n integer matrix grid, where you can move from a cell to any adjacent cell
 * in all 4 directions.
 *
 * Return the number of strictly increasing paths in the grid such that you can start from any cell
 * and end at any cell. Since the answer may be very large, return it modulo 10^9 + 7.
 *
 * Two paths are considered different if they do not have exactly the same sequence of visited
 * cells.
 *
 * ! m == grid.length
 * ! n == grid[i].length
 * ! 1 <= m, n <= 1000
 * ! 1 <= m * n <= 10^5
 * ! 1 <= grid[i][j] <= 10^5
 */

class Solution {
public:
    int countPaths(std::vector<std::vector<int>>& grid)
    {
        const int m = grid.size();
        const int n = grid[0].size();
        std::vector<std::vector<int>> memo(m, std::vector<int>(n, -1));
        int result = 0;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                result = (result + dfs(memo, i, j, grid)) % kMod;
            }
        }
        return result;
    }

private:
    static constexpr int kMod = 1e9 + 7;

    // num of strictly increasing paths starting from grid[x][y]
    int dfs(std::vector<std::vector<int>>& memo, int x, int y, const std::vector<std::vector<int>>& grid)
    {
        static const std::vector<std::pair<int, int>> kDirections{{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        if (memo[x][y] != -1)
            return memo[x][y];

        int result = 1;
        for (const auto& [dx, dy] : kDirections) {
            const int i = x + dx;
            const int j = y + dy;
            if (i < 0 || i >= grid.size() || j < 0 || j >= grid[0].size())
                continue;

            if (grid[i][j] > grid[x][y]) {
                result = (result + dfs(memo, i, j, grid)) % kMod;
            }
        }
        return memo[x][y] = result;
    }
};