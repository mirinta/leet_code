#include <vector>

/**
 * You are given an m x n matrix grid of positive integers. Your task is to determine if it is possible to make either
 * one horizontal or one vertical cut on the grid such that:
 *
 * - Each of the two resulting sections formed by the cut is non-empty.
 *
 * - The sum of the elements in both sections is equal.
 *
 * Return true if such a partition exists; otherwise return false.
 *
 * ! 1 <= m == grid.length <= 10^5
 * ! 1 <= n == grid[i].length <= 10^5
 * ! 2 <= m * n <= 10^5
 * ! 1 <= grid[i][j] <= 10^5
 */

class Solution {
public:
    bool canPartitionGrid(std::vector<std::vector<int>>& grid)
    {
        const int m = grid.size();
        const int n = grid[0].size();
        long long total = 0;
        std::vector<long long> rows(m, 0);
        std::vector<long long> cols(n, 0);
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                total += grid[i][j];
                rows[i] += grid[i][j];
                cols[j] += grid[i][j];
            }
        }
        if (total % 2)
            return false;

        return isValid(rows, total) || isValid(cols, total);
    }

private:
    bool isValid(const std::vector<long long>& nums, long long total)
    {
        long long sum = 0;
        for (const auto& val : nums) {
            sum += val;
            if (sum * 2 == total)
                return true;
        }
        return false;
    }
};
