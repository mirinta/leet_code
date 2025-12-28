#include <queue>
#include <tuple>
#include <vector>

/**
 * You are starving and you want to eat food as quickly as possible. You want to find the shortest
 * path to arrive at any food cell.
 *
 * You are given an m x n character matrix, grid, of these different types of cells:
 *
 * - '*' is your location. There is exactly one '*' cell.
 *
 * - '#' is a food cell. There may be multiple food cells.
 *
 * - 'O' is free space, and you can travel through these cells.
 *
 * - 'X' is an obstacle, and you cannot travel through these cells.
 *
 * You can travel to any adjacent cell north, east, south, or west of your current location if there
 * is not an obstacle.
 *
 * Return the length of the shortest path for you to reach any food cell. If there is no path for
 * you to reach food, return -1.
 *
 * ! m == grid.length
 * ! n == grid[i].length
 * ! 1 <= m, n <= 200
 * ! grid[row][col] is '*', 'X', 'O', or '#'.
 * ! The grid contains exactly one '*'.
 */

class Solution {
public:
    int getFood(std::vector<std::vector<char>>& grid)
    {
        static const std::vector<std::pair<int, int>> kDirections{{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        const int m = grid.size();
        const int n = grid[0].size();
        int startX = -1;
        int startY = -1;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == '*') {
                    startX = i;
                    startY = j;
                    break;
                }
            }
            if (startX != -1 && startY != -1)
                break;
        }
        std::vector<std::vector<bool>> visited(m, std::vector<bool>(n, false));
        visited[startX][startY] = true;
        std::queue<std::tuple<int, int, int>> queue; // <x, y, distance>
        queue.emplace(startX, startY, 0);
        while (!queue.empty()) {
            const auto [x, y, dist] = queue.front();
            queue.pop();
            if (grid[x][y] == '#')
                return dist;

            for (const auto& [dx, dy] : kDirections) {
                const int i = x + dx;
                const int j = y + dy;
                if (i < 0 || i >= m || j < 0 || j >= n)
                    continue;

                if (!visited[i][j] && grid[i][j] != 'X') {
                    visited[i][j] = true;
                    queue.emplace(i, j, dist + 1);
                }
            }
        }
        return -1;
    }
};