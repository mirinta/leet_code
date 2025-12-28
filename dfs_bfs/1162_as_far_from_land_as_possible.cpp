#include <queue>
#include <vector>

/**
 * Given an n x n grid containing only values 0 and 1, where 0 represents water and 1 represents
 * land, find a water cell such that its distance to the nearest land cell is maximized, and return
 * the distance. If no land or water exists in the grid, return -1.
 *
 * The distance used in this problem is the Manhattan distance: the distance between two cells (x0,
 * y0) and (x1, y1) is |x0 - x1| + |y0 - y1|.
 *
 * ! n == grid.length
 * ! n == grid[i].length
 * ! 1 <= n <= 100
 * ! grid[i][j] is 0 or 1
 */

class Solution {
public:
    int shortestBridge(std::vector<std::vector<int>>& grid)
    {
        const int n = grid.size();
        std::queue<std::pair<int, int>> queue;
        bool foundIsland = false;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == 1) {
                    foundIsland = true;
                    dfs(queue, grid, i, j, n);
                    break;
                }
            }
            if (foundIsland)
                break;
        }
        int result = 0;
        while (!queue.empty()) {
            for (int k = queue.size(); k > 0; --k) {
                const auto [x, y] = queue.front();
                queue.pop();
                for (const auto& [dx, dy] : kDirections) {
                    const int i = x + dx;
                    const int j = y + dy;
                    if (i < 0 || i >= n || j < 0 || j >= n)
                        continue;

                    if (grid[i][j] == 1)
                        return result;

                    if (grid[i][j] == 0) {
                        grid[i][j] = 2;
                        queue.emplace(i, j);
                    }
                }
            }
            result++;
        }
        return -1;
    }

private:
    static const std::vector<std::pair<int, int>> kDirections;

    int dfs(std::queue<std::pair<int, int>>& queue, std::vector<std::vector<int>>& grid, int x, int y, int n)
    {
        grid[x][y] = 2;
        int count = 0;
        for (const auto& [dx, dy] : kDirections) {
            const int i = x + dx;
            const int j = y + dy;
            if (i < 0 || i >= n || j < 0 || j >= n)
                continue;

            count += grid[i][j] != 0;
            if (grid[i][j] == 1) {
                dfs(queue, grid, i, j, n);
            }
        }
        if (count < 4) {
            queue.emplace(x, y); // just consider the cells that are on the border
        }
        return 1;
    }
};
const std::vector<std::pair<int, int>> Solution::kDirections{{0, -1}, {0, 1}, {-1, 0}, {1, 0}};