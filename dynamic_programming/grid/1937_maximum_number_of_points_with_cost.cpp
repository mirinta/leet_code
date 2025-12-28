#include <algorithm>
#include <vector>

/**
 * You are given an m x n integer matrix points (0-indexed). Starting with 0 points, you want to
 * maximize the number of points you can get from the matrix.
 *
 * To gain points, you must pick one cell in each row. Picking the cell at coordinates (r, c) will
 * add points[r][c] to your score.
 *
 * However, you will lose points if you pick a cell too far from the cell that you picked in the
 * previous row. For every two adjacent rows r and r + 1 (where 0 <= r < m - 1), picking cells at
 * coordinates (r, c1) and (r + 1, c2) will subtract abs(c1 - c2) from your score.
 *
 * Return the maximum number of points you can achieve.
 *
 * abs(x) is defined as:
 *
 * - x for x >= 0.
 *
 * - -x for x < 0.
 *
 * ! m == points.length
 * !n == points[r].length
 * !1 <= m, n <= 10^5
 * !1 <= m * n <= 10^5
 * !0 <= points[r][c] <= 10^5
 */

class Solution {
public:
    long long maxPoints(std::vector<std::vector<int>>& points)
    {
        // dp[i][j] = max points moving from first row to (i,j)
        // dp[i][j] = std::max(dp[i-1][c] + points[i][j] - std::abs(j-c)) for c in [0,n-1]
        // if j >= c, dp[i][j] = points[i][j] + std::max(dp[i-1][c] + c - j) for c in [0,j]
        // if j <= c, dp[i][j] = points[i][j] + std::max(dp[i-1][c] - c + j) for c in [j,n-1]
        const int m = points.size();
        const int n = points[0].size();
        std::vector<std::vector<long long>> dp(m, std::vector<long long>(n));
        for (int j = 0; j < n; ++j) {
            dp[0][j] = points[0][j];
        }
        for (int i = 1; i < m; ++i) {
            long long prefixMax = LLONG_MIN;
            for (int j = 0; j < n; ++j) {
                prefixMax = std::max(prefixMax, dp[i - 1][j] + j);
                dp[i][j] = std::max(dp[i][j], points[i][j] + prefixMax - j);
            }
            long long suffixMax = LLONG_MIN;
            for (int j = n - 1; j >= 0; --j) {
                suffixMax = std::max(suffixMax, dp[i - 1][j] - j);
                dp[i][j] = std::max(dp[i][j], points[i][j] + suffixMax + j);
            }
        }
        return *std::max_element(dp[m - 1].begin(), dp[m - 1].end());
    }
};