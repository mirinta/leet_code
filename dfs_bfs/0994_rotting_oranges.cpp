#include <queue>
#include <vector>

/**
 * You are given an m x n grid where each cell can have one of three values:
 *
 * - 0 representing an empty cell,
 *
 * - 1 representing a fresh orange, or
 *
 * - 2 representing a rotten orange.
 * Every minute, any fresh orange that is 4-directionally adjacent to a rotten orange becomes
 * rotten.
 *
 * Return the minimum number of minutes that must elapse until no cell has a fresh orange. If this
 * is impossible, return -1.
 *
 * ! m == grid.length
 * ! n == grid[i].length
 * ! 1 <= m, n <= 10
 * ! grid[i][j] is 0, 1, or 2.
 */

class Solution {
public:
    int orangesRotting(std::vector<std::vector<int>>& grid)
    {
        static const std::vector<std::pair<int, int>> kDirections{{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        const int m = grid.size();
        const int n = grid[0].size();
        int fresh = 0;
        std::queue<std::pair<int, int>> queue;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == 2) {
                    queue.emplace(i, j);
                } else if (grid[i][j] == 1) {
                    fresh++;
                }
            }
        }
        if (fresh == 0)
            return 0;

        int result = 0;
        while (!queue.empty() && fresh > 0) {
            for (int k = queue.size(); k > 0; --k) {
                const auto [x, y] = queue.front();
                queue.pop();
                for (const auto& [dx, dy] : kDirections) {
                    const int i = x + dx;
                    const int j = y + dy;
                    if (i < 0 || i >= m || j < 0 || j >= n || grid[i][j] != 1)
                        continue;

                    fresh--;
                    grid[i][j] = 2;
                    queue.emplace(i, j);
                }
            }
            result++;
        }
        return fresh == 0 ? result : -1;
    }
};