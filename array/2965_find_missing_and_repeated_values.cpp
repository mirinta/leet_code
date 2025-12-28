#include <vector>

/**
 * You are given a 0-indexed 2D integer matrix grid of size n * n with values in the range [1, n2].
 * Each integer appears exactly once except a which appears twice and b which is missing. The task
 * is to find the repeating and missing numbers a and b.
 *
 * Return a 0-indexed integer array ans of size 2 where ans[0] equals to a and ans[1] equals to b.
 *
 * ! 2 <= n == grid.length == grid[i].length <= 50
 * ! 1 <= grid[i][j] <= n * n
 * ! For all x that 1 <= x <= n * n there is exactly one x that is not equal to any of the grid
 * ! members.
 * ! For all x that 1 <= x <= n * n there is exactly one x that is equal to exactly two of
 * ! the grid members.
 * ! For all x that 1 <= x <= n * n except two of them there is exactly one pair of i, j that 0 <=
 * ! i, j <= n - 1 and grid[i][j] == x.
 */

class Solution {
public:
    std::vector<int> findMissingAndRepeatedValues(std::vector<std::vector<int>>& grid)
    {
        const int n = grid.size();
        std::vector<int> count(n * n + 1, 0);
        std::vector<int> result;
        result.reserve(2);
        for (const auto& row : grid) {
            for (const auto& val : row) {
                if (++count[val] > 1) {
                    result.push_back(val);
                }
            }
        }
        for (int val = 1; val < count.size(); ++val) {
            if (count[val] == 0) {
                result.push_back(val);
                return result;
            }
        }
        return {};
    }
};
