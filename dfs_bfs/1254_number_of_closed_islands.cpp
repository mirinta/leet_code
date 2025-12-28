#include <vector>

/**
 * Given a 2D grid consists of 0s (land) and 1s (water).  An island is a maximal 4-directionally
 * connected group of 0s and a closed island is an island totally (all left, top, right, bottom)
 * surrounded by 1s.
 *
 * Return the number of closed islands.
 *
 * ! 1 <= grid.length, grid[0].length <= 100
 * ! 0 <= grid[i][j] <=1
 */

class Solution {
public:
    int closedIsland(std::vector<std::vector<int>>& grid)
    {
        const int m = grid.size();
        const int n = grid[0].size();
        for (int i = 0; i < m; ++i) {
            if (grid[i][0] == 0) {
                dfs(grid, i, 0);
            }
            if (grid[i][n - 1] == 0) {
                dfs(grid, i, n - 1);
            }
        }
        for (int j = 0; j < n; ++j) {
            if (grid[0][j] == 0) {
                dfs(grid, 0, j);
            }
            if (grid[m - 1][j] == 0) {
                dfs(grid, m - 1, j);
            }
        }
        int result = 0;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == 0) {
                    result++;
                    dfs(grid, i, j);
                }
            }
        }
        return result;
    }

private:
    void dfs(std::vector<std::vector<int>>& grid, int i, int j)
    {
        if (i < 0 || i >= grid.size() || j < 0 || j >= grid[0].size() || grid[i][j] != 0)
            return;

        grid[i][j] = 1;
        dfs(grid, i - 1, j);
        dfs(grid, i + 1, j);
        dfs(grid, i, j - 1);
        dfs(grid, i, j + 1);
    }
};
