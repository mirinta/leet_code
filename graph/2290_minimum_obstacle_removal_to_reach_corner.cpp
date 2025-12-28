#include <deque>
#include <vector>

/**
 * You are given a 0-indexed 2D integer array grid of size m x n. Each cell has one of two values:
 *
 * - 0 represents an empty cell,
 *
 * - 1 represents an obstacle that may be removed.
 *
 * You can move up, down, left, or right from and to an empty cell.
 *
 * Return the minimum number of obstacles to remove so you can move from the upper left corner (0,
 * 0) to the lower right corner (m - 1, n - 1).
 *
 * ! m == grid.length
 * ! n == grid[i].length
 * ! 1 <= m, n <= 10^5
 * ! 2 <= m * n <= 10^5
 * ! grid[i][j] is either 0 or 1.
 * ! grid[0][0] == grid[m - 1][n - 1] == 0
 */

class Solution {
public:
    int minimumObstacles(std::vector<std::vector<int>>& grid)
    {
        static const std::vector<std::pair<int, int>> kDirections{{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        const int m = grid.size();
        const int n = grid[0].size();
        std::vector<std::vector<int>> minObstaclesTo(m, std::vector<int>(n, INT_MAX));
        minObstaclesTo[0][0] = 0;
        std::deque<std::tuple<int, int, int>> queue;
        queue.emplace_back(0, 0, 0);
        while (!queue.empty()) {
            const auto [count, x, y] = queue.front();
            queue.pop_front();
            for (const auto& [dx, dy] : kDirections) {
                const int i = x + dx;
                const int j = y + dy;
                if (i < 0 || i >= m || j < 0 || j >= n)
                    continue;

                if (minObstaclesTo[i][j] != INT_MAX)
                    continue;

                if (grid[i][j] == 1) {
                    minObstaclesTo[i][j] = count + 1;
                    queue.emplace_back(count + 1, i, j);
                } else {
                    minObstaclesTo[i][j] = count;
                    queue.emplace_front(count, i, j);
                }
            }
        }
        return minObstaclesTo[m - 1][n - 1];
    }
};