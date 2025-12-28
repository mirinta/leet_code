#include <array>
#include <queue>
#include <vector>

/**
 * You are given an m x n grid grid of values 0, 1, or 2, where:
 *
 * - each 0 marks an empty land that you can pass by freely,
 *
 * - each 1 marks a building that you cannot pass through, and
 *
 * - each 2 marks an obstacle that you cannot pass through.
 *
 * You want to build a house on an empty land that reaches all buildings in the shortest total
 * travel distance. You can only move up, down, left, and right.
 *
 * Return the shortest travel distance for such a house. If it is not possible to build such a house
 * according to the above rules, return -1.
 *
 * The total travel distance is the sum of the distances between the houses of the friends and the
 * meeting point.
 *
 * The distance is calculated using Manhattan Distance, where distance(p1, p2) = |p2.x - p1.x| +
 * |p2.y - p1.y|.
 *
 * ! m == grid.length
 * ! n == grid[i].length
 * ! 1 <= m, n <= 50
 * ! grid[i][j] is either 0, 1, or 2.
 * ! There will be at least one building in the grid.
 */

class Solution {
public:
    int shortestDistance(std::vector<std::vector<int>>& grid)
    {
        const int m = grid.size();
        const int n = grid[0].size();
        int buildings = 0;
        std::vector<std::vector<std::array<int, 2>>> data(m, std::vector<std::array<int, 2>>(n, {0, 0}));
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == 1) {
                    buildings++;
                    bfs(data, i, j, grid);
                }
            }
        }
        int result = INT_MAX;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                const auto& [dist, count] = data[i][j];
                if (count == buildings) {
                    result = std::min(result, dist);
                }
            }
        }
        return result == INT_MAX ? -1 : result;
    }

private:
    void bfs(std::vector<std::vector<std::array<int, 2>>>& data,
             int x0,
             int y0,
             const std::vector<std::vector<int>>& grid)
    {
        static const std::vector<std::pair<int, int>> kDirections{{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
        const int m = grid.size();
        const int n = grid[0].size();
        std::vector<std::vector<bool>> visited(m, std::vector<bool>(n, false));
        visited[x0][y0] = true;
        std::queue<std::pair<int, int>> queue;
        queue.emplace(x0, y0);
        int dist = 0;
        while (!queue.empty()) {
            for (int t = queue.size(); t > 0; --t) {
                const auto [x, y] = queue.front();
                queue.pop();
                if (grid[x][y] == 0) {
                    data[x][y][0] += dist;
                    data[x][y][1]++;
                }
                for (const auto& [dx, dy] : kDirections) {
                    const int i = x + dx;
                    const int j = y + dy;
                    if (i < 0 || i >= m || j < 0 || j >= n)
                        continue;

                    if (!visited[i][j] && grid[i][j] == 0) {
                        visited[i][j] = true;
                        queue.emplace(i, j);
                    }
                }
            }
            dist++;
        }
    }
};