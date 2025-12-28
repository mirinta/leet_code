#include <functional>
#include <vector>

/**
 * You are given an m x n binary grid grid where 1 represents land and 0 represents water. An island
 * is a maximal 4-directionally (horizontal or vertical) connected group of 1's.
 *
 * The grid is said to be connected if we have exactly one island, otherwise is said disconnected.
 *
 * In one day, we are allowed to change any single land cell (1) into a water cell (0).
 *
 * Return the minimum number of days to disconnect the grid.
 *
 * ! m == grid.length
 * ! n == grid[i].length
 * ! 1 <= m, n <= 30
 * ! grid[i][j] is either 0 or 1.
 */

class Solution {
public:
    int minDays(std::vector<std::vector<int>>& grid)
    {
        if (numOfIslands(grid) != 1)
            return 0;

        const int m = grid.size();
        const int n = grid[0].size();
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == 0)
                    continue;

                grid[i][j] = 0;
                if (numOfIslands(grid) != 1)
                    return 1;

                grid[i][j] = 1;
            }
        }
        return 2;
    }

private:
    int numOfIslands(const std::vector<std::vector<int>>& grid)
    {
        const int m = grid.size();
        const int n = grid[0].size();
        std::vector<std::vector<bool>> visited(m, std::vector<bool>(n, false));
        std::function<void(int, int)> dfs = [&](int i, int j) {
            if (i < 0 || i >= m || j < 0 || j >= n)
                return;

            if (grid[i][j] != 1 || visited[i][j])
                return;

            visited[i][j] = true;
            dfs(i + 1, j);
            dfs(i - 1, j);
            dfs(i, j + 1);
            dfs(i, j - 1);
        };
        int result = 0;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == 1 && !visited[i][j]) {
                    dfs(i, j);
                    result++;
                }
            }
        }
        return result;
    }
};