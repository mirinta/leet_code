#include <unordered_map>
#include <vector>

/**
 * You are given an m x n grid. Each cell of grid represents a street. The street of grid[i][j] can
 * be:
 *
 * - 1 which means a street connecting the left cell and the right cell.
 *
 * - 2 which means a street connecting the upper cell and the lower cell.
 *
 * - 3 which means a street connecting the left cell and the lower cell.
 *
 * - 4 which means a street connecting the right cell and the lower cell.
 *
 * - 5 which means a street connecting the left cell and the upper cell.
 *
 * - 6 which means a street connecting the right cell and the upper cell.
 *
 * ! m == grid.length
 * ! n == grid[i].length
 * ! 1 <= m, n <= 300
 * ! 1 <= grid[i][j] <= 6
 */

class Solution {
public:
    bool hasValidPath(std::vector<std::vector<int>>& grid)
    {
        const int m = grid.size();
        const int n = grid[0].size();
        visited = std::vector<std::vector<bool>>(m, std::vector<bool>(n, false));
        return dfs(0, 0, -1, -1, m, n, grid);
    }

private:
    static const std::unordered_map<int, std::vector<std::pair<int, int>>> map;
    std::vector<std::vector<bool>> visited;

    bool dfs(int x, int y, int srcX, int srcY, int m, int n, const std::vector<std::vector<int>>& grid)
    {
        if (!isValid(x, y, srcX, srcY, grid))
            return false;

        if (x == m - 1 && y == n - 1)
            return true;

        visited[x][y] = true;
        for (const auto& [dx, dy] : map.at(grid[x][y])) {
            const int i = x + dx;
            const int j = y + dy;
            if (i < 0 || i >= m || j < 0 || j >= n || visited[i][j])
                continue;

            if (dfs(i, j, x, y, m, n, grid))
                return true;
        }
        return false;
    }

    bool isValid(int x, int y, int srcX, int srcY, const std::vector<std::vector<int>>& grid)
    {
        if (srcX == -1 && srcY == -1)
            return true;

        for (const auto& [dx, dy] : map.at(grid[x][y])) {
            const int i = x + dx;
            const int j = y + dy;
            if (i == srcX && j == srcY)
                return true;
        }
        return false;
    }
};
const std::unordered_map<int, std::vector<std::pair<int, int>>> Solution::map{
    {1, {{0, -1}, {0, 1}}}, {2, {{-1, 0}, {1, 0}}},  {3, {{0, -1}, {1, 0}}},
    {4, {{0, 1}, {1, 0}}},  {5, {{0, -1}, {-1, 0}}}, {6, {{0, 1}, {-1, 0}}}};