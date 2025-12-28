#include <array>
#include <vector>

/**
 * Given an integer array nums, return the maximum possible sum of elements of the array such that
 * it is divisible by three.
 *
 * ! 1 <= nums.length <= 4 * 10^4
 * ! 1 <= nums[i] <= 10^4
 */

class Solution {
public:
    int maxSumDivThree(std::vector<int>& nums)
    {
        // dp[i][j] = maximum sum of nums[0:i-1] that the sum % 3 = j
        const int n = nums.size();
        std::vector<std::array<int, 3>> dp(n + 1, {0, INT_MIN, INT_MIN});
        for (int i = 1; i <= n; ++i) {
            for (int j = 0; j < 3; ++j) {
                const int target = (j - nums[i - 1] % 3 + 3) % 3;
                dp[i][j] = std::max(dp[i - 1][j], nums[i - 1] + dp[i - 1][target]);
            }
        }
        return dp[n][0];
    }
};