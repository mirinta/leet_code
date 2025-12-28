#include <vector>

/**
 * You are given an m x n integer matrix mat and an integer target.
 *
 * Choose one integer from each row in the matrix such that the absolute difference between target
 * and the sum of the chosen elements is minimized.
 *
 * Return the minimum absolute difference.
 *
 * The absolute difference between two numbers a and b is the absolute value of a - b.
 *
 * ! m == mat.length
 * ! n == mat[i].length
 * ! 1 <= m, n <= 70
 * ! 1 <= mat[i][j] <= 70
 * ! 1 <= target <= 800
 */

class Solution {
public:
    int minimizeTheDifference(std::vector<std::vector<int>>& mat, int target)
    {
        // dp[i][j] = whether the sum from row 0 to row i is equal to j
        const int m = mat.size();
        const int n = mat[0].size();
        bool dp[70][4901];
        std::memset(dp, false, sizeof(dp));
        for (int i = 0; i < n; ++i) {
            dp[0][mat[0][i]] = true;
        }
        for (int i = 1; i < m; ++i) {
            for (int j = 0; j < 4901; ++j) {
                if (!dp[i - 1][j])
                    continue;

                for (const auto& val : mat[i]) {
                    dp[i][j + val] = true;
                }
            }
        }
        int result = INT_MAX;
        for (int j = 0; j < 4901; ++j) {
            if (dp[m - 1][j]) {
                result = std::min(result, std::abs(j - target));
            }
        }
        return result;
    }
};