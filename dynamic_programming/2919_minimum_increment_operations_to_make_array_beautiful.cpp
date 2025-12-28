#include <vector>

/**
 * You are given a 0-indexed integer array nums having length n, and an integer k.
 *
 * You can perform the following increment operation any number of times (including zero):
 *
 * Choose an index i in the range [0, n - 1], and increase nums[i] by 1.
 * An array is considered beautiful if, for any subarray with a size of 3 or more, its maximum
 * element is greater than or equal to k.
 *
 * Return an integer denoting the minimum number of increment operations needed to make nums
 * beautiful.
 *
 * A subarray is a contiguous non-empty sequence of elements within an array.
 *
 * ! 3 <= n == nums.length <= 10^5
 * ! 0 <= nums[i] <= 10^9
 * ! 0 <= k <= 10^9
 */

class Solution {
public:
    long long minIncrementOperations(std::vector<int>& nums, int k)
    {
        return approach2(nums, k);
    }

private:
    // DP with space optimization, time O(N), space O(1)
    long long approach2(const std::vector<int>& nums, int k)
    {
        const int n = nums.size();
        long long dpIMinus3 = std::max(0, k - nums[0]);
        long long dpIMinus2 = std::max(0, k - nums[1]);
        long long dpIMinus1 = std::max(0, k - nums[2]);
        for (int i = 3; i < n; ++i) {
            auto dpI = std::min({dpIMinus3, dpIMinus2, dpIMinus1}) + std::max(0, k - nums[i]);
            dpIMinus3 = dpIMinus2;
            dpIMinus2 = dpIMinus1;
            dpIMinus1 = dpI;
        }
        return std::min({dpIMinus3, dpIMinus2, dpIMinus1});
    }

    // DP, time O(N), space O(N)
    long long approach1(const std::vector<int>& nums, int k)
    {
        // we only consider the subarrays with length of 3
        // dp[i] = min num of operations to make nums[0:i] beautiful while having nums[i] >= k
        // X X i-3 i-2 i-1 i
        //         |<----->|
        const int n = nums.size();
        std::vector<long long> dp(n);
        dp[0] = std::max(0, k - nums[0]);
        dp[1] = std::max(0, k - nums[1]);
        dp[2] = std::max(0, k - nums[2]);
        for (int i = 3; i < n; ++i) {
            dp[i] = std::min({dp[i - 3], dp[i - 2], dp[i - 1]}) + std::max(0, k - nums[i]);
        }
        // the last subarray with length of 3 = {nums[i-3], nums[i-2], nums[i-1]}
        return std::min({dp[n - 3], dp[n - 2], dp[n - 1]});
    }
};
