#include <queue>
#include <vector>

/**
 * You are given an integer matrix isWater of size m x n that represents a map of land and water
 * cells.
 *
 * - If isWater[i][j] == 0, cell (i, j) is a land cell.
 *
 * - If isWater[i][j] == 1, cell (i, j) is a water cell.
 *
 * You must assign each cell a height in a way that follows these rules:
 *
 * - The height of each cell must be non-negative.
 *
 * - If the cell is a water cell, its height must be 0.
 *
 * - Any two adjacent cells must have an absolute height difference of at most 1. A cell is adjacent
 * to another cell if the former is directly north, east, south, or west of the latter (i.e., their
 * sides are touching).
 *
 * Find an assignment of heights such that the maximum height in the matrix is maximized.
 *
 * Return an integer matrix height of size m x n where height[i][j] is cell (i, j)'s height. If
 * there are multiple solutions, return any of them.
 *
 * ! m == isWater.length
 * ! n == isWater[i].length
 * ! 1 <= m, n <= 1000
 * ! isWater[i][j] is 0 or 1.
 * ! There is at least one water cell.
 */

class Solution {
public:
    std::vector<std::vector<int>> highestPeak(std::vector<std::vector<int>>& isWater)
    {
        static const std::vector<std::pair<int, int>> kDirections{{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        const int m = isWater.size();
        const int n = isWater[0].size();
        std::vector<std::vector<int>> result(m, std::vector<int>(n, -1));
        std::queue<std::pair<int, int>> queue;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (isWater[i][j]) {
                    result[i][j] = 0;
                    queue.emplace(i, j);
                }
            }
        }
        while (!queue.empty()) {
            for (int k = queue.size(); k > 0; --k) {
                const auto [x, y] = queue.front();
                queue.pop();
                for (const auto& [dx, dy] : kDirections) {
                    const int i = x + dx;
                    const int j = y + dy;
                    if (i < 0 || i >= m || j < 0 || j >= n)
                        continue;

                    if (result[i][j] == -1) {
                        result[i][j] = result[x][y] + 1;
                        queue.emplace(i, j);
                    }
                }
            }
        }
        return result;
    }
};
