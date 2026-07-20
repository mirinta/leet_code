#include <vector>

/**
 * Given a 2D grid of size m x n and an integer k. You need to shift the grid k times.
 *
 * In one shift operation:
 *
 * - Element at grid[i][j] moves to grid[i][j + 1].
 *
 * - Element at grid[i][n - 1] moves to grid[i + 1][0].
 *
 * - Element at grid[m - 1][n - 1] moves to grid[0][0].
 *
 * Return the 2D grid after applying shift operation k times.
 *
 * ! m == grid.length
 * ! n == grid[i].length
 * ! 1 <= m <= 50
 * ! 1 <= n <= 50
 * ! -1000 <= grid[i][j] <= 1000
 * ! 0 <= k <= 100
 */

class Solution {
public:
    std::vector<std::vector<int>> shiftGrid(std::vector<std::vector<int>>& grid, int k)
    {
        const int m = grid.size();
        const int n = grid[0].size();
        const int count = m * n;
        auto encode = [&](int i, int j) { return i * n + j; };
        auto decode = [&](int v) { return std::make_pair(v / n, v % n); };
        std::vector<std::vector<int>> result(m, std::vector<int>(n));
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                const auto [x, y] = decode((encode(i, j) + k) % count);
                result[x][y] = grid[i][j];
            }
        }
        return result;
    }
};