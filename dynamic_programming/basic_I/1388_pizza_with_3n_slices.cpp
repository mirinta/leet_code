#include <array>
#include <vector>

/**
 * There is a pizza with 3n slices of varying size, you and your friends will take slices of pizza
 * as follows:
 *
 * - You will pick any pizza slice.
 *
 * - Your friend Alice will pick the next slice in the anti-clockwise direction of your pick.
 *
 * - Your friend Bob will pick the next slice in the clockwise direction of your pick.
 *
 * - Repeat until there are no more slices of pizzas.
 *
 * Given an integer array slices that represent the sizes of the pizza slices in a clockwise
 * direction, return the maximum possible sum of slice sizes that you can pick.
 *
 * ! 3 * n == slices.length
 * ! 1 <= slices.length <= 500
 * ! 1 <= slices[i] <= 1000
 */

class Solution {
public:
    int maxSizeSlices(std::vector<int>& slices)
    {
        const int n = slices.size();
        return std::max(helper(0, n - 2, n / 3, slices), helper(1, n - 1, n / 3, slices));
    }

private:
    // max sum of picking at most k slices from slices[lo:hi]
    int helper(int lo, int hi, int k, const std::vector<int>& slices)
    {
        // dp[i][j][0] = max sum of picking at most j slices from slices[0:i-1] while slices[i-1] is
        // not picked
        // dp[i][j][1] = max sum of picking at most j slices from slices[0:i-1] while slices[i-1] is
        // picked
        const int n = hi - lo + 1;
        std::vector<std::vector<std::array<int, 2>>> dp(n + 1, std::vector<std::array<int, 2>>(1 + k, {0, 0}));
        dp[0][0][1] = INT_MIN;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= k; ++j) {
                dp[i][j][0] = std::max(dp[i - 1][j][0], dp[i - 1][j][1]);
                dp[i][j][1] = dp[i - 1][j - 1][0] + slices[lo + i - 1];
            }
        }
        return std::max(dp[n][k][0], dp[n][k][1]);
    }
};