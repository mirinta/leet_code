#include <vector>

/**
 * You are given an m x n binary matrix grid, where 0 represents a sea cell and 1 represents a land
 * cell.
 *
 * A move consists of walking from one land cell to another adjacent (4-directionally) land cell or
 * walking off the boundary of the grid.
 *
 * Return the number of land cells in grid for which we cannot walk off the boundary of the grid in
 * any number of moves.
 *
 * ! m == grid.length
 * ! n == grid[i].length
 * ! 1 <= m, n <= 500
 * ! grid[i][j] is either 0 or 1.
 */

class Solution {
public:
    // DFS, time O(MN), space O(MN)
    int numEnclaves(const std::vector<std::vector<int>>& grid)
    {
        const int m = grid.size();
        const int n = grid[0].size();
        // flood all islands that connect with the boundaries
        // - mark the cells as "visited"
        std::vector<std::vector<bool>> visited(m, std::vector<bool>(n, false));
        for (int i = 0; i < m; ++i) {
            if (grid[i][0] == 1 && !visited[i][0]) {
                dfs(visited, i, 0, grid);
            }
            if (grid[i][n - 1] == 1 && !visited[i][n - 1]) {
                dfs(visited, i, n - 1, grid);
            }
        }
        for (int j = 0; j < n; ++j) {
            if (grid[0][j] == 1 && !visited[0][j]) {
                dfs(visited, 0, j, grid);
            }
            if (grid[m - 1][j] == 1 && !visited[m - 1][j]) {
                dfs(visited, m - 1, j, grid);
            }
        }
        // count the total number of land cells
        int result = 0;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == 1 && !visited[i][j]) {
                    result++;
                }
            }
        }
        return result;
    }

private:
    void dfs(std::vector<std::vector<bool>>& visited, int x, int y, const std::vector<std::vector<int>>& grid)
    {
        static const std::vector<std::pair<int, int>> kDirections{{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        const int m = grid.size();
        const int n = grid[0].size();
        visited[x][y] = true;
        for (const auto& [dx, dy] : kDirections) {
            const int i = x + dx;
            const int j = y + dy;
            if (i < 0 || i >= m || j < 0 || j >= n)
                continue;

            if (grid[i][j] == 1 && !visited[i][j]) {
                dfs(visited, i, j, grid);
            }
        }
    }
};
