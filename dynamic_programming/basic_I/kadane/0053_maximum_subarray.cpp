#include <vector>

/**
 * Given an integer array "nums", find the sub-array with the largest sum, and return its sum.
 *
 * ! 1 <= nums.length <= 10^5
 * ! -10^4 <= nums[i] <= 10^4
 */

class Solution {
public:
    int maxSubArray(std::vector<int>& nums)
    {
        return approach2(nums);
    }

private:
    // Kadane's algorithm, time O(N), space O(1)
    int approach2(const std::vector<int>& nums)
    {
        int result = INT_MIN;
        int sum = 0;
        for (const auto& val : nums) {
            sum += val;
            if (sum > result) {
                result = sum;
            }
            if (sum < 0) {
                sum = 0;
            }
        }
        return result;
    }

    // DP, time O(N), space O(N)
    int approach1(const std::vector<int>& nums)
    {
        const int n = nums.size();
        // dp[i] = largest subarray sum that ends with nums[i]
        std::vector<int> dp(n, INT_MIN);
        dp[0] = nums[0];
        int result = dp[0];
        for (int i = 1; i < n; ++i) {
            dp[i] = std::max(nums[i], nums[i] + dp[i - 1]);
            result = std::max(result, dp[i]);
        }
        return result;
    }
};