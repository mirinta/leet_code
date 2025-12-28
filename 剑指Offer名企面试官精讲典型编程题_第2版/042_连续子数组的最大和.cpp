#include <vector>

/**
 * 输入一个整型数组，数组中的一个或连续多个整数组成一个子数组。求所有子数组的和的最大值。
 *
 * ! 要求时间复杂度为O(n)。
 *
 * ! 1 <= arr.length <= 10^5
 * ! -100 <= arr[i] <= 100
 *
 * ! 本题与LC 53相同。
 */

class Solution {
public:
    int maxSubArray(std::vector<int>& nums)
    {
        // Kadane's algorithm:
        int sum = 0;
        int result = INT_MIN;
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

private:
    int approach1(std::vector<int>& nums)
    {
        if (nums.empty())
            return INT_MIN;

        // dp[i] = max sum of nums[0:i]
        const int n = nums.size();
        std::vector<int> dp(n, 0);
        dp[0] = nums[0];
        for (int i = 1; i < n; ++i) {
            // choices:
            // - make a new subarray starts with nums[i], or
            // - put nums[i] at the end of the previous subarray
            dp[i] = std::max(nums[i], dp[i - 1] + nums[i]);
        }
        int result = INT_MIN;
        for (const auto& val : dp) {
            result = std::max(result, val);
        }
        return result;
    }
};