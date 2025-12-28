#include <vector>

/**
 * You are given two m x n binary matrices grid1 and grid2 containing only 0's (representing water)
 * and 1's (representing land). An island is a group of 1's connected 4-directionally (horizontal or
 * vertical). Any cells outside of the grid are considered water cells.
 *
 * An island in grid2 is considered a sub-island if there is an island in grid1 that contains all
 * the cells that make up this island in grid2.
 *
 * Return the number of islands in grid2 that are considered sub-islands.
 *
 * ! m == grid1.length == grid2.length
 * ! n == grid1[i].length == grid2[i].length
 * ! 1 <= m, n <= 500
 * ! grid1[i][j] and grid2[i][j] are either 0 or 1.
 */

class Solution {
public:
    int countSubIslands(std::vector<std::vector<int>>& grid1, std::vector<std::vector<int>>& grid2)
    {
        const int m = grid1.size();
        const int n = grid1[0].size();
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid2[i][j] == 1 && grid1[i][j] == 0) {
                    dfs(grid2, i, j);
                }
            }
        }
        int result = 0;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid2[i][j] == 1) {
                    result++;
                    dfs(grid2, i, j);
                }
            }
        }
        return result;
    }

private:
    void dfs(std::vector<std::vector<int>>& grid, int i, int j)
    {
        if (i < 0 || i >= grid.size() || j < 0 || j >= grid[0].size())
            return;

        if (grid[i][j] == 0)
            return;

        grid[i][j] = 0;
        dfs(grid, i + 1, j);
        dfs(grid, i - 1, j);
        dfs(grid, i, j + 1);
        dfs(grid, i, j - 1);
    }
};