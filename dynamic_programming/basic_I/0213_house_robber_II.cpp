#include <array>
#include <vector>

/**
 * You are a professional robber planning to rob houses along a street. Each house has a certain
 * amount of money stashed. All houses at this place are arranged in a circle. That means the first
 * house is the neighbor of the last one. Meanwhile, adjacent houses have a security system
 * connected, and it will automatically contact the police if two adjacent houses were broken into
 * on the same night.
 *
 * Given an integer array "nums" representing the amount of money of each house, return the maximum
 * amount of money you can rob tonight without alerting the police.
 *
 * ! nums[i] >= 0
 */

class Solution {
public:
    int rob(std::vector<int>& nums)
    {
        if (nums.size() == 1)
            return nums[0];

        const int n = nums.size();
        return std::max(helper(0, n - 2, nums), helper(1, n - 1, nums));
    }

private:
    // max amount of money to rob nums[lo:hi]
    int helper(int lo, int hi, const std::vector<int>& nums)
    {
        // dp[i][0] = max amount of money to rob nums[lo:i-1] while nums[i-1] is not robbed
        // dp[i][1] = max amount of money to rob nums[lo:i-1] while nums[i-1] is robbed
        const int n = hi - lo + 1;
        std::vector<std::array<int, 2>> dp(n + 1, {0, 0});
        dp[0][1] = INT_MIN;
        for (int i = 1; i <= n; ++i) {
            dp[i][0] = std::max(dp[i - 1][0], dp[i - 1][1]);
            dp[i][1] = dp[i - 1][0] + nums[lo + i - 1];
        }
        return std::max(dp[n][0], dp[n][1]);
    }
};