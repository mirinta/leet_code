#include <queue>
#include <vector>

/**
 * There is an m x n rectangular island that borders both the Pacific Ocean and Atlantic Ocean. The
 * Pacific Ocean touches the island's left and top edges, and the Atlantic Ocean touches the
 * island's right and bottom edges.
 *
 * The island is partitioned into a grid of square cells. You are given an m x n integer matrix
 * heights where heights[r][c] represents the height above sea level of the cell at coordinate (r,
 * c).
 *
 * The island receives a lot of rain, and the rain water can flow to neighboring cells directly
 * north, south, east, and west if the neighboring cell's height is less than or equal to the
 * current cell's height. Water can flow from any cell adjacent to an ocean into the ocean.
 *
 * Return a 2D list of grid coordinates result where result[i] = [ri, ci] denotes that rain water
 * can flow from cell (ri, ci) to both the Pacific and Atlantic oceans.
 *
 * ! m == heights.length
 * ! n == heights[r].length
 * ! 1 <= m, n <= 200
 * ! 0 <= heights[r][c] <= 10^5
 */

class Solution {
public:
    std::vector<std::vector<int>> pacificAtlantic(std::vector<std::vector<int>>& heights)
    {
        const int m = heights.size();
        const int n = heights[0].size();
        std::queue<std::pair<int, int>> pacific;
        std::queue<std::pair<int, int>> atlantic;
        for (int i = 0; i < m; ++i) {
            pacific.emplace(i, 0);
            atlantic.emplace(i, n - 1);
        }
        for (int j = 0; j < n; ++j) {
            pacific.emplace(0, j);
            atlantic.emplace(m - 1, j);
        }
        const auto pacificReachable = bfs(pacific, heights);
        const auto atlanticReachable = bfs(atlantic, heights);
        std::vector<std::vector<int>> result;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (pacificReachable[i][j] && atlanticReachable[i][j]) {
                    result.push_back({i, j});
                }
            }
        }
        return result;
    }

private:
    static const std::vector<std::pair<int, int>> kDirections;

    std::vector<std::vector<bool>> bfs(std::queue<std::pair<int, int>>& queue,
                                       const std::vector<std::vector<int>>& grid)
    {
        const int m = grid.size();
        const int n = grid[0].size();
        std::vector<std::vector<bool>> visited(m, std::vector<bool>(n, false));
        while (!queue.empty()) {
            for (int k = queue.size(); k > 0; --k) {
                const auto [x, y] = queue.front();
                queue.pop();
                visited[x][y] = true;
                for (const auto& [dx, dy] : kDirections) {
                    const int i = x + dx;
                    const int j = y + dy;
                    if (i < 0 || i >= m || j < 0 || j >= n)
                        continue;

                    if (!visited[i][j] && grid[i][j] >= grid[x][y]) {
                        queue.emplace(i, j);
                    }
                }
            }
        }
        return visited;
    }
};
const std::vector<std::pair<int, int>> Solution::kDirections{{0, 1}, {0, -1}, {1, 0}, {-1, 0}};