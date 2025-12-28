#include <vector>

/**
 * You are given an m x n integer matrix grid, and three integers row, col, and color. Each value in
 * the grid represents the color of the grid square at that location.
 *
 * Two squares are called adjacent if they are next to each other in any of the 4 directions.
 *
 * Two squares belong to the same connected component if they have the same color and they are
 * adjacent.
 *
 * The border of a connected component is all the squares in the connected component that are either
 * adjacent to (at least) a square not in the component, or on the boundary of the grid (the first
 * or last row or column).
 *
 * You should color the border of the connected component that contains the square grid[row][col]
 * with color.
 *
 * Return the final grid.
 *
 * ! m == grid.length
 * ! n == grid[i].length
 * ! 1 <= m, n <= 50
 * ! 1 <= grid[i][j], color <= 1000
 * ! 0 <= row < m
 * ! 0 <= col < n
 */

class Solution {
public:
    std::vector<std::vector<int>> colorBorder(std::vector<std::vector<int>>& grid, int row, int col, int color)
    {
        if (grid[row][col] == color)
            return grid;

        const int m = grid.size();
        const int n = grid[0].size();
        std::vector<std::vector<bool>> visited(m, std::vector<bool>(n, false));
        std::vector<std::pair<int, int>> border;
        dfs(border, visited, row, col, grid[row][col], grid);
        for (const auto& [x, y] : border) {
            grid[x][y] = color;
        }
        return grid;
    }

private:
    static const std::vector<std::pair<int, int>> kDirections;

    void dfs(std::vector<std::pair<int, int>>& border,
             std::vector<std::vector<bool>>& visited,
             int i,
             int j,
             int color,
             const std::vector<std::vector<int>>& grid)
    {
        if (onBorder(i, j, grid)) {
            border.emplace_back(i, j);
        }
        visited[i][j] = true;
        for (const auto& [dx, dy] : kDirections) {
            const int x = i + dx;
            const int y = j + dy;
            if (x < 0 || x >= grid.size() || y < 0 || y >= grid[0].size())
                continue;

            if (!visited[x][y] && grid[x][y] == color) {
                dfs(border, visited, x, y, color, grid);
            }
        }
    }

    bool onBorder(int i, int j, const std::vector<std::vector<int>>& grid)
    {
        for (const auto& [dx, dy] : kDirections) {
            const int x = i + dx;
            const int y = j + dy;
            if (x < 0 || x >= grid.size() || y < 0 || y >= grid[0].size())
                return true;

            if (grid[x][y] != grid[i][j])
                return true;
        }
        return false;
    }
};
const std::vector<std::pair<int, int>> Solution::kDirections{{0, 1}, {0, -1}, {1, 0}, {-1, 0}};