#include <vector>

/**
 * You are given an n x n integer matrix grid.
 *
 * Generate an integer matrix maxLocal of size (n - 2) x (n - 2) such that:
 *
 * - maxLocal[i][j] is equal to the largest value of the 3 x 3 matrix in grid centered around row i
 * + 1 and column j + 1.
 *
 * In other words, we want to find the largest value in every contiguous 3 x 3 matrix in grid.
 *
 * Return the generated matrix.
 *
 * ! n == grid.length == grid[i].length
 * ! 3 <= n <= 100
 * ! 1 <= grid[i][j] <= 100
 */

class Solution {
public:
    std::vector<std::vector<int>> largestLocal(std::vector<std::vector<int>>& grid)
    {
        const int n = grid.size();
        std::vector<std::vector<int>> result;
        result.reserve(n - 2);
        for (int i = 1; i <= n - 2; ++i) {
            std::vector<int> v;
            v.reserve(n - 2);
            for (int j = 1; j <= n - 2; ++j) {
                v.push_back(helper(i, j, grid));
            }
            result.push_back(std::move(v));
        }
        return result;
    }

private:
    int helper(int centerX, int centerY, const std::vector<std::vector<int>>& grid)
    {
        int max = INT_MIN;
        for (int i = centerX - 1; i <= centerX + 1; ++i) {
            for (int j = centerY - 1; j <= centerY + 1; ++j) {
                max = std::max(max, grid[i][j]);
            }
        }
        return max;
    }
};