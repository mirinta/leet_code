#include <vector>

/**
 * You are given a 0-indexed array nums of n integers and an integer target.

 * You are initially positioned at index 0. In one step, you can jump from index i to any index j such that:
 *
 * - 0 <= i < j < n
 *
 * - -target <= nums[j] - nums[i] <= target
 *
 * Return the maximum number of jumps you can make to reach index n - 1.
 *
 * If there is no way to reach index n - 1, return -1.
 *
 * ! 2 <= nums.length == n <= 1000
 * ! -10^9 <= nums[i] <= 10^9
 * ! 0 <= target <= 2 * 10^9
 */

class Solution {
public:
    int maximumJumps(std::vector<int>& nums, int target)
    {
        // dp[i] = max num of jumps to move from 0 to i
        const int n = nums.size();
        std::vector<int> dp(n, INT_MIN);
        dp[0] = 0;
        for (int i = 1; i < n; ++i) {
            for (int j = 0; j < i; ++j) {
                if (std::abs(nums[i] - nums[j]) <= target) {
                    dp[i] = std::max(dp[i], 1 + dp[j]);
                }
            }
        }
        return dp[n - 1] < 0 ? -1 : dp[n - 1];
    }
};