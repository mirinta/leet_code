#include <numeric>
#include <vector>

/**
 * You are installing a billboard and want it to have the largest height. The billboard will have
 * two steel supports, one on each side. Each steel support must be an equal height.
 *
 * You are given a collection of rods that can be welded together. For example, if you have rods of
 * lengths 1, 2, and 3, you can weld them together to make a support of length 6.
 *
 * Return the largest possible height of your billboard installation. If you cannot support the
 * billboard, return 0.
 *
 * ! 1 <= rods.length <= 20
 * ! 1 <= rods[i] <= 1000
 * ! sum(rods[i]) <= 5000
 */

class Solution {
public:
    int tallestBillboard(std::vector<int>& rods)
    {
        // dp[i][j] = max height of the shorter steel support using rods[0:i)
        // while the absolute difference between the shorter and taller support is j
        const int n = rods.size();
        const int m = std::accumulate(rods.begin(), rods.end(), 0);
        std::vector<std::vector<int>> dp(n + 1, std::vector<int>(m + 1, INT_MIN));
        dp[0][0] = 0;
        for (int i = 1; i <= n; ++i) {
            const int curr = rods[i - 1];
            for (int j = 0; j <= m; ++j) {
                // case 1: current rod is not picked
                dp[i][j] = std::max(dp[i][j], dp[i - 1][j]);
                // case 2: add current rod to the taller support
                if (j + curr <= m) {
                    dp[i][j + curr] = std::max(dp[i][j + curr], dp[i - 1][j]);
                }
                // case 3: add current rod to the shorter support
                // let x = height of the original shorter support = dp[i-1][j]
                //     y = height of the original taller support = dp[i-1][j] + j
                // - if x + curr <= y, then diff = j - curr
                //   and height of the new shorter support = x + curr
                //   i.e., dp[i][j-curr] = dp[i-1][j] + curr
                // - if x + curr > y, then diff = curr - j
                //   and height of the new shorter support
                //   i.e., dp[i][curr-j] = dp[i-1][j] + j
                // - in summary, dp[i][abs(j-curr)] = dp[i-1][j] + min(curr,j)
                const int diff = std::abs(j - curr);
                dp[i][diff] = std::max(dp[i][diff], dp[i - 1][j] + std::min(curr, j));
            }
        }
        return dp[n][0];
    }
};