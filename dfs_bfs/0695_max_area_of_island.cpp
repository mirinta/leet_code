#include <vector>

/**
 * You are given an m x n binary matrix grid. An island is a group of 1's (representing land)
 * connected 4-directionally (horizontal or vertical.) You may assume all four edges of the grid are
 * surrounded by water.
 *
 * The area of an island is the number of cells with a value 1 in the island.
 *
 * Return the maximum area of an island in grid. If there is no island, return 0.
 *
 * ! m == grid.length
 * ! n == grid[i].length
 * ! 1 <= m, n <= 50
 * ! grid[i][j] is either 0 or 1.
 */

class Solution {
public:
    int maxAreaOfIsland(std::vector<std::vector<int>>& grid)
    {
        const int m = grid.size();
        const int n = grid[0].size();
        int result = 0;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j]) {
                    result = std::max(result, dfs(grid, i, j, m, n));
                }
            }
        }
        return result;
    }

private:
    int dfs(std::vector<std::vector<int>>& grid, int i, int j, int m, int n)
    {
        if (i < 0 || i >= m || j < 0 || j >= n || grid[i][j] == 0)
            return 0;

        grid[i][j] = 0;
        int area = 1;
        area += dfs(grid, i + 1, j, m, n);
        area += dfs(grid, i - 1, j, m, n);
        area += dfs(grid, i, j + 1, m, n);
        area += dfs(grid, i, j - 1, m, n);
        return area;
    }
};
