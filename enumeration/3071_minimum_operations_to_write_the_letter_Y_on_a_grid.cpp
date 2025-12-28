#include <vector>

/**
 * You are given a 0-indexed n x n grid where n is odd, and grid[r][c] is 0, 1, or 2.
 *
 * We say that a cell belongs to the Letter Y if it belongs to one of the following:
 *
 * - The diagonal starting at the top-left cell and ending at the center cell of the grid.
 *
 * - The diagonal starting at the top-right cell and ending at the center cell of the grid.
 *
 * - The vertical line starting at the center cell and ending at the bottom border of the grid.
 *
 * The Letter Y is written on the grid if and only if:
 *
 * - All values at cells belonging to the Y are equal.
 *
 * - All values at cells not belonging to the Y are equal.
 *
 * - The values at cells belonging to the Y are different from the values at cells not belonging to
 * the Y.
 *
 * Return the minimum number of operations needed to write the letter Y on the grid given that in
 * one operation you can change the value at any cell to 0, 1, or 2.
 *
 * ! 3 <= n <= 49
 * ! n == grid.length == grid[i].length
 * ! 0 <= grid[i][j] <= 2
 * ! n is odd.
 */

class Solution {
public:
    int minimumOperationsToWriteY(std::vector<std::vector<int>>& grid)
    {
        const int n = grid.size();
        const int mid = n / 2;
        // if (x,y) belongs to Y, then mask[i][j] = true
        std::vector<std::vector<bool>> mask(n, std::vector<bool>(n, false));
        for (int i = 0, j1 = 0, j2 = n - 1; i < mid; ++i, ++j1, --j2) {
            mask[i][j1] = true;
            mask[i][j2] = true;
        }
        for (int i = mid; i < n; ++i) {
            mask[i][mid] = true;
        }
        int result = INT_MAX;
        for (int y = 0; y < 3; ++y) {
            for (int x = 0; x < 3; ++x) {
                if (x == y)
                    continue;

                result = std::min(result, solve(y, x, mask, grid));
            }
        }
        return result;
    }

private:
    int solve(int Y, int notY, const std::vector<std::vector<bool>>& mask, const std::vector<std::vector<int>>& grid)
    {
        const int n = grid.size();
        int result = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                result += grid[i][j] != (mask[i][j] ? Y : notY);
            }
        }
        return result;
    }
};