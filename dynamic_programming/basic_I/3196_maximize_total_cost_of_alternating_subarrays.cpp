#include <array>
#include <vector>

/**
 * You are given an integer array nums with length n.

 * The cost of a subarray nums[l..r], where 0 <= l <= r < n, is defined as:
 *
 * cost(l, r) = nums[l] - nums[l + 1] + ... + nums[r] * (−1)r − l
 *
 * Your task is to split nums into subarrays such that the total cost of the subarrays is maximized,
 * ensuring each element belongs to exactly one subarray.
 *
 * Formally, if nums is split into k subarrays, where k > 1, at indices i1, i2, ..., ik − 1, where 0
 * <= i1 < i2 < ... < ik - 1 < n - 1, then the total cost will be:
 *
 * cost(0, i1) + cost(i1 + 1, i2) + ... + cost(ik − 1 + 1, n − 1)
 *
 * Return an integer denoting the maximum total cost of the subarrays after splitting the array
 * optimally.
 *
 * Note: If nums is not split into subarrays, i.e. k = 1, the total cost is simply cost(0, n - 1).
 *
 * ! 1 <= nums.length <= 10^5
 * ! -10^9 <= nums[i] <= 10^9
 */

class Solution {
public:
    long long maximumTotalCost(std::vector<int>& nums)
    {
        return approach2(nums);
    }

private:
    long long approach2(const std::vector<int>& nums)
    {
        const int n = nums.size();
        long long negative = LLONG_MIN / 2;
        long long positive = nums[0];
        for (int i = 1; i < n; ++i) {
            const long long backup = positive;
            positive = nums[i] + std::max(negative, positive);
            negative = backup - nums[i];
        }
        return std::max(positive, negative);
    }

    long long approach1(const std::vector<int>& nums)
    {
        // dp[i][0] = max cost of splitting nums[0:i] while the sign of nums[i] is +1
        // dp[i][1] = max cost of splitting nums[0:i] while the sign of nums[i] is -1
        const int n = nums.size();
        std::vector<std::array<long long, 2>> dp(n, {LLONG_MIN / 2, LLONG_MIN / 2});
        dp[0][0] = nums[0];
        for (int i = 1; i < n; ++i) {
            dp[i][0] = nums[i] + std::max(dp[i - 1][0], dp[i - 1][1]);
            dp[i][1] = dp[i - 1][0] - nums[i];
        }
        return std::max(dp[n - 1][0], dp[n - 1][1]);
    }
};