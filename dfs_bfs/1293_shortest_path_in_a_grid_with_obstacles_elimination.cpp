#include <queue>
#include <vector>

/**
 * You are given an m x n integer matrix grid where each cell is either 0 (empty) or 1 (obstacle).
 * You can move up, down, left, or right from and to an empty cell in one step.
 *
 * Return the minimum number of steps to walk from the upper left corner (0, 0) to the lower right
 * corner (m - 1, n - 1) given that you can eliminate at most k obstacles. If it is not possible to
 * find such walk return -1.
 *
 * ! m == grid.length
 * ! n == grid[i].length
 * ! 1 <= m, n <= 40
 * ! 1 <= k <= m * n
 * ! grid[i][j] is either 0 or 1.
 * ! grid[0][0] == grid[m - 1][n - 1] == 0
 */

class Solution {
public:
    int shortestPath(std::vector<std::vector<int>>& grid, int k)
    {
        static const std::vector<std::pair<int, int>> kDirections{{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
        const int m = grid.size();
        const int n = grid[0].size();
        std::vector<std::vector<std::vector<bool>>> visited(
            m, std::vector<std::vector<bool>>(n, std::vector<bool>(k + 1, false)));
        visited[0][0][0] = true;
        std::queue<std::tuple<int, int, int>> queue; // <x, y, num of eliminated walls>
        queue.emplace(0, 0, 0);
        int result = 0;
        while (!queue.empty()) {
            for (int t = queue.size(); t > 0; --t) {
                const auto [x, y, count] = queue.front();
                queue.pop();
                if (x == m - 1 && y == n - 1)
                    return result;

                for (const auto& [dx, dy] : kDirections) {
                    const int i = x + dx;
                    const int j = y + dy;
                    if (i < 0 || i >= m || j < 0 || j >= n)
                        continue;

                    if (grid[i][j] == 0 && visited[i][j][count])
                        continue;

                    if (grid[i][j] == 1 && (count == k || visited[i][j][count + 1]))
                        continue;

                    visited[i][j][count + grid[i][j]] = true;
                    queue.emplace(i, j, count + grid[i][j]);
                }
            }
            result++;
        }
        return -1;
    }
};