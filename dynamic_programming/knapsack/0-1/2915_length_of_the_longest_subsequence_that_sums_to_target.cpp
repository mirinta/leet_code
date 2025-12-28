#include <vector>

/**
 * You are given a 0-indexed array of integers nums, and an integer target.
 *
 * Return the length of the longest subsequence of nums that sums up to target. If no such
 * subsequence exists, return -1.
 *
 * A subsequence is an array that can be derived from another array by deleting some or no elements
 * without changing the order of the remaining elements.
 *
 * ! 1 <= nums.length <= 1000
 * ! 1 <= nums[i] <= 1000
 * ! 1 <= target <= 1000
 */

class Solution {
public:
    int lengthOfLongestSubsequence(std::vector<int>& nums, int target)
    {
        return approach2(nums, target);
    }

private:
    int approach2(const std::vector<int>& nums, int target)
    {
        std::vector<int> dp(1 + target, -1);
        dp[0] = 0;
        for (const auto& val : nums) {
            for (int j = target; j >= 1; --j) {
                if (j - val >= 0 && dp[j - val] != -1) {
                    dp[j] = std::max(dp[j], 1 + dp[j - val]);
                }
            }
        }
        return dp[target];
    }

    int approach1(const std::vector<int>& nums, int target)
    {
        // dp[i][j] = length of the longest subsequence of nums[0:i-1] ending at nums[i-1]
        // that sums up to j
        const int n = nums.size();
        std::vector<std::vector<int>> dp(n + 1, std::vector<int>(1 + target, -1));
        for (int i = 0; i <= n; ++i) {
            dp[i][0] = 0;
        }
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= target; ++j) {
                dp[i][j] = dp[i - 1][j];
                if (j - nums[i - 1] >= 0 && dp[i - 1][j - nums[i - 1]] != -1) {
                    dp[i][j] = std::max(dp[i][j], 1 + dp[i - 1][j - nums[i - 1]]);
                }
            }
        }
        return dp[n][target];
    }
};