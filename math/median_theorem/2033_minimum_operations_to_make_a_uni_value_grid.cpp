#include <algorithm>
#include <vector>

/**
 * You are given a 2D integer grid of size m x n and an integer x. In one operation, you can add x
 * to or subtract x from any element in the grid.
 *
 * A uni-value grid is a grid where all the elements of it are equal.
 *
 * Return the minimum number of operations to make the grid uni-value. If it is not possible, return
 * -1.
 *
 * ! m == grid.length
 * ! n == grid[i].length
 * ! 1 <= m, n <= 10^5
 * ! 1 <= m * n <= 10^5
 * ! 1 <= x, grid[i][j] <= 10^4
 */

class Solution {
public:
    int minOperations(std::vector<std::vector<int>>& grid, int x)
    {
        const int m = grid.size();
        const int n = grid[0].size();
        std::vector<int> values;
        values.reserve(m * n);
        for (const auto& row : grid) {
            for (const auto& val : row) {
                values.push_back(val);
            }
        }
        std::sort(values.begin(), values.end());
        const int median = values[values.size() / 2];
        int result = 0;
        for (const auto& val : values) {
            if (std::abs(val - median) % x != 0)
                return -1;

            result += std::abs(val - median) / x;
        }
        return result;
    }
};