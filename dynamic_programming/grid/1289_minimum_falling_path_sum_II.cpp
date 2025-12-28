#include <algorithm>
#include <vector>

/**
 * Given an n x n integer matrix "grid", return the minimum sum of falling path with non-zero
 * shifts.
 *
 * A falling path with non-zero shifts is a choice of exactly one element from each row of "grid"
 * such that no two elements chosen in adjacent rows are in the same column.
 *
 * ! n == grid.length == grid[i].length
 * ! 1 <= n <= 200
 * ! -99 <= grid[i][j] <= 99
 */

class Solution {
public:
    int minFallingPathSum(std::vector<std::vector<int>>& grid)
    {
        return approach2(grid);
    }

private:
    // DP with time and optimization, TC = O(N^2), SC = O(N)
    int approach2(const std::vector<std::vector<int>>& grid)
    {
        const int n = grid.size();
        auto dp = grid[0];
        for (int i = 1; i < n; ++i) {
            const auto [minIdx, minVal, secondMinIdx, secondMinVal] = helper(dp);
            for (int j = 0; j < n; ++j) {
                if (j == minIdx) {
                    dp[j] = grid[i][j] + secondMinVal;
                } else {
                    dp[j] = grid[i][j] + minVal;
                }
            }
        }
        return *std::min_element(dp.begin(), dp.end());
    }

    std::tuple<int, int, int, int> helper(const std::vector<int>& nums)
    {
        const int n = nums.size();
        int minIdx = -1;
        int minVal = INT_MAX;
        int secondMinIdx = -1;
        int secondMinVal = INT_MAX;
        for (int i = 0; i < n; ++i) {
            if (nums[i] < minVal) {
                secondMinIdx = minIdx;
                secondMinVal = minVal;
                minVal = nums[i];
                minIdx = i;
            } else if (nums[i] < secondMinVal) {
                secondMinVal = nums[i];
                secondMinIdx = i;
            }
        }
        return std::make_tuple(minIdx, minVal, secondMinIdx, secondMinVal);
    }

    // DP, TC = O(N^3), SC = O(N^2)
    int approach1(const std::vector<std::vector<int>>& grid)
    {
        // dp[i][j] = min sum of a valid path from the first row to (i,j)
        const int n = grid.size();
        std::vector<std::vector<int>> dp(n, std::vector<int>(n, INT_MAX));
        for (int j = 0; j < n; ++j) {
            dp[0][j] = grid[0][j];
        }
        for (int i = 1; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                for (int k = 0; k < n; ++k) {
                    if (j == k)
                        continue;

                    dp[i][j] = std::min(dp[i][j], grid[i][j] + dp[i - 1][k]);
                }
            }
        }
        return *std::min_element(dp[n - 1].begin(), dp[n - 1].end());
    }
};