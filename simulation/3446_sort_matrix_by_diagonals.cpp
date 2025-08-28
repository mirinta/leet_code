#include <algorithm>
#include <vector>

/**
 * You are given an n x n square matrix of integers grid. Return the matrix such that:
 *
 * - The diagonals in the bottom-left triangle (including the middle diagonal) are sorted in
 * non-increasing order.
 *
 * - The diagonals in the top-right triangle are sorted in non-decreasing order.
 *
 * ! grid.length == grid[i].length == n
 * ! 1 <= n <= 10
 * ! -10^5 <= grid[i][j] <= 10^5
 */

class Solution
{
public:
    std::vector<std::vector<int>> sortMatrix(std::vector<std::vector<int>>& grid)
    {
        const int n = grid.size();
        std::vector<int> vals;
        std::vector<std::pair<int, int>> indices;
        auto helper = [&](int x, int y, int index) {
            vals.clear();
            vals.reserve(n - index);
            indices.clear();
            indices.reserve(n - index);
            while (x >= 0 && x < n && y >= 0 && y < n) {
                vals.emplace_back(grid[x][y]);
                indices.emplace_back(x, y);
                x++;
                y++;
            }
        };
        for (int row = n - 1; row >= 0; --row) {
            helper(row, 0, row);
            std::sort(vals.begin(), vals.end(), std::greater<>());
            for (int i = 0; i < indices.size(); ++i) {
                grid[indices[i].first][indices[i].second] = vals[i];
            }
        }
        for (int col = 1; col < n; ++col) {
            helper(0, col, col);
            std::sort(vals.begin(), vals.end());
            for (int i = 0; i < indices.size(); ++i) {
                grid[indices[i].first][indices[i].second] = vals[i];
            }
        }
        return grid;
    }
};
