#include <vector>

/**
 * You are given row x col grid representing a map where grid[i][j] = 1 represents land and
 * grid[i][j] = 0 represents water.
 *
 * Grid cells are connected horizontally/vertically (not diagonally). The grid is completely
 * surrounded by water, and there is exactly one island (i.e., one or more connected land cells).
 *
 * The island doesn't have "lakes", meaning the water inside isn't connected to the water around the
 * island. One cell is a square with side length 1. The grid is rectangular, width and height don't
 * exceed 100. Determine the perimeter of the island.
 *
 * ! row == grid.length
 * ! col == grid[i].length
 * ! 1 <= row, col <= 100
 * ! grid[i][j] is 0 or 1.
 * ! There is exactly one island in grid.
 */

class Solution {
public:
    int islandPerimeter(std::vector<std::vector<int>>& grid)
    {
        const int m = grid.size();
        const int n = grid[0].size();
        int result = 0;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == 0)
                    continue;

                result += helper(i, j, grid);
            }
        }
        return result;
    }

private:
    int helper(int i, int j, const std::vector<std::vector<int>>& grid)
    {
        const int m = grid.size();
        const int n = grid[0].size();
        static const std::vector<std::pair<int, int>> kDirections{{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        int result = 0;
        for (const auto& [dx, dy] : kDirections) {
            const int x = i + dx;
            const int y = j + dy;
            result += x < 0 || x >= m || y < 0 || y >= n || grid[x][y] == 0;
        }
        return result;
    }
};