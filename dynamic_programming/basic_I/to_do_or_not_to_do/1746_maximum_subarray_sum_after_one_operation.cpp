#include <array>
#include <vector>

/**
 * You are given an integer array nums. You must perform exactly one operation where you can replace
 * one element nums[i] with nums[i] * nums[i].
 *
 * Return the maximum possible subarray sum after exactly one operation. The subarray must be
 * non-empty.
 *
 * ! 1 <= nums.length <= 10^5
 * ! -10^4 <= nums[i] <= 10^4
 */

class Solution {
public:
    int maxSumAfterOperation(std::vector<int>& nums)
    {
        // dp[i][0] = max subarray sum of nums[0:i-1] ending at nums[i-1] and the operation is not
        // applied
        // dp[i][1] = max subarray sum of nums[0:i-1] ending at nums[i-1] and the operation is
        // applied
        const int n = nums.size();
        std::vector<std::array<int, 2>> dp(n + 1, {INT_MIN / 2, INT_MIN / 2});
        int result = INT_MIN;
        for (int i = 1; i <= n; ++i) {
            const int val = nums[i - 1];
            const int squared = val * val;
            dp[i][0] = std::max(val, dp[i - 1][0] + val);
            dp[i][1] = std::max({val, dp[i - 1][1] + val, squared, dp[i - 1][0] + squared});
            result = std::max(result, dp[i][1]);
        }
        return result;
    }
};
