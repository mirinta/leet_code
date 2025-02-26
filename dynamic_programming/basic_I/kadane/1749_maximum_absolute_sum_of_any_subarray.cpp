#include <array>
#include <vector>

/**
 * You are given an integer array nums. The absolute sum of a subarray [numsl, numsl+1, ...,
 * numsr-1, numsr] is abs(numsl + numsl+1 + ... + numsr-1 + numsr).
 *
 * Return the maximum absolute sum of any (possibly empty) subarray of nums.
 *
 * Note that abs(x) is defined as follows:
 *
 * - If x is a negative integer, then abs(x) = -x.
 *
 * - If x is a non-negative integer, then abs(x) = x.
 *
 * ! 1 <= nums.length <= 10^5
 * ! -10^4 <= nums[i] <= 10^4
 */

class Solution
{
public:
    int maxAbsoluteSum(std::vector<int>& nums) { return approach2(nums); }

private:
    int approach2(const std::vector<int>& nums)
    {
        int min = 0;
        int max = 0;
        int result = 0;
        for (const auto& val : nums) {
            min = std::min(val, min + val);
            max = std::max(val, max + val);
            result = std::max({result, std::abs(min), std::abs(max)});
        }
        return result;
    }

    int approach1(const std::vector<int>& nums)
    {
        // dp[i][0] = min subarray sum of nums[0:i] ending at nums[i]
        // dp[i][1] = max subarray sum of nums[0:i] ending at nums[i]
        const int n = nums.size();
        std::vector<std::array<int, 2>> dp(n, {0, 0});
        dp[0] = {nums[0], nums[0]};
        int result = std::max(std::abs(dp[0][0]), std::abs(dp[0][1]));
        for (int i = 1; i < n; ++i) {
            dp[i][0] = std::min(nums[i], dp[i - 1][0] + nums[i]);
            dp[i][1] = std::max(nums[i], dp[i - 1][1] + nums[i]);
            result = std::max({result, std::abs(dp[i][0]), std::abs(dp[i][1])});
        }
        return result;
    }
};
