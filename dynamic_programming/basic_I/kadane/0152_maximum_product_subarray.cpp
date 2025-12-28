#include <array>
#include <vector>

/**
 * Given an integer array nums, find a subarray that has the largest product, and return the
 * product.
 *
 * The test cases are generated so that the answer will fit in a 32-bit integer.
 *
 * ! 1 <= nums.length <= 2 * 10^4
 * ! -10 <= nums[i] <= 10
 * ! The product of any prefix or suffix of nums is guaranteed to fit in a 32-bit integer.
 */

class Solution {
public:
    int maxProduct(std::vector<int>& nums)
    {
        return approach2(nums);
    }

private:
    // DP with space optimization, TC = O(N), SC = O(1)
    int approach2(const std::vector<int>& nums)
    {
        double max = 1;
        double min = 1;
        double result = INT_MIN;
        for (const double val : nums) {
            const double backup = min;
            min = std::min({val, val * min, val * max});
            max = std::max({val, val * backup, val * max});
            result = std::max(result, max);
        }
        return result;
    }

    // DP, TC = O(N), SC = O(N)
    int approach1(const std::vector<int>& nums)
    {
        // dp[i][0] = min subarray product of nums[0:i-1] ending at nums[i-1]
        // dp[i][1] = max subarray product of nums[0:i-1] ending at nums[i-1]
        const int n = nums.size();
        std::vector<std::array<double, 2>> dp(n + 1);
        dp[0] = {1, 1};
        double result = INT_MIN;
        for (int i = 1; i <= n; ++i) {
            const double val = nums[i - 1];
            const double case1 = val * dp[i - 1][0];
            const double case2 = val * dp[i - 1][1];
            dp[i][0] = std::min({val, case1, case2});
            dp[i][1] = std::max({val, case1, case2});
            result = std::max(result, dp[i][1]);
        }
        return result;
    }
};