#include <vector>

/**
 * Given a m * n matrix of ones and zeros, return how many square submatrices have all ones.
 *
 * ! 1 <= arr.length <= 300
 * ! 1 <= arr[0].length <= 300
 * ! 0 <= arr[i][j] <= 1
 */

class Solution {
public:
    int countSquares(std::vector<std::vector<int>>& matrix)
    {
        return approach2(matrix);
    }

private:
    // DP with space optimization, TC = O(MN), SC = O(N)
    int approach2(const std::vector<std::vector<int>>& matrix)
    {
        const int m = matrix.size();
        const int n = matrix[0].size();
        std::vector<int> dp(n, 0);
        int result = 0;
        for (int j = 0; j < n; ++j) {
            dp[j] = matrix[0][j] == 1;
            result += dp[j];
        }
        for (int i = 1; i < m; ++i) {
            auto prev = dp;
            std::fill(dp.begin(), dp.end(), 0);
            dp[0] = matrix[i][0] == 1;
            result += dp[0];
            for (int j = 1; j < n; ++j) {
                if (matrix[i][j] == 0)
                    continue;

                dp[j] = 1 + std::min({prev[j - 1], prev[j], dp[j - 1]});
                result += dp[j];
            }
        }
        return result;
    }

    // DP, TC = O(MN), SC = O(MN)
    int approach1(const std::vector<std::vector<int>>& matrix)
    {
        // similar to LC 221
        // dp[i][j] = length of the largest square whose bottom-right corner is matrix[i][j]
        // count of squares = sum of all dp[i][j]
        const int m = matrix.size();
        const int n = matrix[0].size();
        std::vector<std::vector<int>> dp(m, std::vector<int>(n, 0));
        int result = 0;
        for (int i = 0; i < m; ++i) {
            dp[i][0] = matrix[i][0] == 1;
            result += dp[i][0];
        }
        for (int j = 1; j < n; ++j) {
            dp[0][j] = matrix[0][j] == 1;
            result += dp[0][j];
        }
        for (int i = 1; i < m; ++i) {
            for (int j = 1; j < n; ++j) {
                if (matrix[i][j] == 0)
                    continue;

                dp[i][j] = 1 + std::min({dp[i - 1][j - 1], dp[i - 1][j], dp[i][j - 1]});
                result += dp[i][j];
            }
        }
        return result;
    }
};