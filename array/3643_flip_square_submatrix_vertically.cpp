#include <vector>

/**
 * You are given an m x n integer matrix grid, and three integers x, y, and k.
 *
 * The integers x and y represent the row and column indices of the top-left corner of a square submatrix and the
 * integer k represents the size (side length) of the square submatrix.
 *
 * Your task is to flip the submatrix by reversing the order of its rows vertically.
 *
 * Return the updated matrix.
 *
 * ! m == grid.length
 * ! n == grid[i].length
 * ! 1 <= m, n <= 50
 * ! 1 <= grid[i][j] <= 100
 * ! 0 <= x < m
 * ! 0 <= y < n
 * ! 1 <= k <= min(m - x, n - y)
 */

class Solution {
public:
    std::vector<std::vector<int>> reverseSubmatrix(std::vector<std::vector<int>>& grid, int x, int y, int k)
    {
        for (int i = x, j = x + k - 1; i < j; ++i, --j) {
            for (int p = y; p <= y + k - 1; ++p) {
                std::swap(grid[i][p], grid[j][p]);
            }
        }
        return grid;
    }
};
