#include <vector>

/**
 * Given an "m x n" binary matrix filled with 0's and 1's, find the largest square containing only
 * 1's and return its area.
 *
 * ! m == matrix.length
 * ! n == matrix[i].length
 * ! 1 <= m, n <= 300
 * ! matrix[i][j] is '0' or '1'.
 */

class Solution {
public:
    int maximalSquare(std::vector<std::vector<char>>& matrix)
    {
        return approach3(matrix);
    }

private:
    // DP with space optimization, TC = O(MN), SC = O(N)
    int approach3(const std::vector<std::vector<char>>& matrix)
    {
        const int m = matrix.size();
        const int n = matrix[0].size();
        std::vector<int> dp(n, 0);
        int maxLength = 0;
        for (int j = 0; j < n; ++j) {
            dp[j] = matrix[0][j] - '0';
            maxLength = std::max(maxLength, dp[j]);
        }
        for (int i = 1; i < m; ++i) {
            auto prev = dp;
            std::fill(dp.begin(), dp.end(), 0);
            dp[0] = matrix[i][0] - '0';
            maxLength = std::max(maxLength, dp[0]);
            for (int j = 1; j < n; ++j) {
                if (matrix[i][j] == '0')
                    continue;

                dp[j] = 1 + std::min({prev[j - 1], prev[j], dp[j - 1]});
                maxLength = std::max(maxLength, dp[j]);
            }
        }
        return maxLength * maxLength;
    }

    // DP, TC = O(MN), SC = O(MN)
    int approach2(const std::vector<std::vector<char>>& matrix)
    {
        const int m = matrix.size();
        const int n = matrix[0].size();
        std::vector<std::vector<int>> dp(m, std::vector<int>(n, 0));
        int maxLength = 0;
        for (int i = 0; i < m; ++i) {
            dp[i][0] = matrix[i][0] - '0';
            maxLength = std::max(maxLength, dp[i][0]);
        }
        for (int j = 0; j < n; ++j) {
            dp[0][j] = matrix[0][j] - '0';
            maxLength = std::max(maxLength, dp[0][j]);
        }
        for (int i = 1; i < m; ++i) {
            for (int j = 1; j < n; ++j) {
                if (matrix[i][j] == '0')
                    continue;

                dp[i][j] = 1 + std::min({dp[i - 1][j - 1], dp[i - 1][j], dp[i][j - 1]});
                maxLength = std::max(maxLength, dp[i][j]);
            }
        }
        return maxLength * maxLength;
    }

    // 2D prefix sum + DP, TC = O(MN), SC = O(MN)
    int approach1(const std::vector<std::vector<char>>& matrix)
    {
        // dp[i][j] = length of the largest square whose bottom-right corner is matrix[i][j]
        // case 1:
        // let dp[i-1][j-1] = L1
        // sum of matrix[i][j-L1:j] = L1+1 = sum of matrix[i-L1:i][j]
        // then dp[i][j] = L1+1
        //
        //     j-L1  j-1 j
        // i-L1 +------+ ?
        //      |      | ?
        //      |      | ?
        //  i-1 +------+ ?
        //    i ???????? X
        //
        // case 2:
        // let dp[i][j-1] = L2
        // if sum of matrix[i-L2][j-L2:j] = L2+1 = sum of matrix[i-L2:i][j]
        // then dp[i][j] = L2+1
        //
        //       j-L2  j-1 j
        //   i-L2 ??????????
        // i-L2+1 +------+ ?
        //        |      | ?
        //        |      | ?
        //      i +------+ X
        //
        // case 3:
        // let dp[i-1][j] = L3
        // if sum of matrix[i-L3:i][j-L3] = L3+1 = sum of matrix[i][j-L3:j]
        // then dp[i][j] = L3+1
        //
        //     j-L3 j-L3+1 j
        //   i-L3 ? +------+
        //        ? |      |
        //        ? |      |
        //    i-1 ? +------+
        //      i ? ???????X
        const int m = matrix.size();
        const int n = matrix[0].size();
        // presum[i][j] = sum of matrix[0:i-1][0:j-1]
        std::vector<std::vector<int>> presum(m + 1, std::vector<int>(n + 1, 0));
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                const int val = matrix[i - 1][j - 1] - '0';
                presum[i][j] = val + presum[i - 1][j] + presum[i][j - 1] - presum[i - 1][j - 1];
            }
        }
        // return sum of matrix[x1:x2][y1:y2]
        auto query = [&m, &n, &presum](int x1, int y1, int x2, int y2) {
            if (x1 < 0 || x1 >= m || y1 < 0 || y1 >= n)
                return 0;

            if (x2 < 0 || x2 >= m || y2 < 0 || y2 >= n)
                return 0;

            return presum[x2 + 1][y2 + 1] - presum[x2 + 1][y1] - presum[x1][y2 + 1] + presum[x1][y1];
        };
        std::vector<std::vector<int>> dp(m, std::vector<int>(n, 0));
        int maxLength = 0;
        for (int i = 0; i < m; ++i) {
            dp[i][0] = matrix[i][0] - '0';
            maxLength = std::max(maxLength, dp[i][0]);
        }
        for (int j = 0; j < n; ++j) {
            dp[0][j] = matrix[0][j] - '0';
            maxLength = std::max(maxLength, dp[0][j]);
        }
        for (int i = 1; i < m; ++i) {
            for (int j = 1; j < n; ++j) {
                if (matrix[i][j] == '0')
                    continue;

                const int L1 = dp[i - 1][j - 1];
                const int L2 = dp[i][j - 1];
                const int L3 = dp[i - 1][j];
                dp[i][j] = 1;
                if (query(i, j - L1, i, j) == L1 + 1 && query(i - L1, j, i, j) == L1 + 1) {
                    dp[i][j] = std::max(dp[i][j], 1 + L1);
                }
                if (query(i - L2, j - L2, i - L2, j) == L2 + 1 && query(i - L2, j, i, j) == L2 + 1) {
                    dp[i][j] = std::max(dp[i][j], 1 + L2);
                }
                if (query(i - L3, j - L3, i, j - L3) == L3 + 1 && query(i, j - L3, i, j) == L3 + 1) {
                    dp[i][j] = std::max(dp[i][j], 1 + L3);
                }
                maxLength = std::max(maxLength, dp[i][j]);
            }
        }
        return maxLength * maxLength;
    }
};
