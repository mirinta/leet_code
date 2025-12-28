#include <array>
#include <numeric>
#include <vector>

/**
 * Given a circular integer array nums of length n, return the maximum possible sum of a non-empty
 * subarray of nums.
 *
 * A circular array means the end of the array connects to the beginning of the array. Formally, the
 * next element of nums[i] is nums[(i + 1) % n] and the previous element of nums[i] is nums[(i - 1 +
 * n) % n].
 *
 * A subarray may only include each element of the fixed buffer nums at most once. Formally, for a
 * subarray nums[i], nums[i + 1], ..., nums[j], there does not exist i <= k1, k2 <= j with k1 % n ==
 * k2 % n.
 *
 * ! n == nums.length
 * ! 1 <= n <= 3 * 10^4
 * ! -3 * 10^4 <= nums[i] <= 3 * 10^4
 */

class Solution {
public:
    int maxSubarraySumCircular(std::vector<int>& nums)
    {
        // case 1: target subarray = nums[i:j]
        // - answer1 = normal way to find max subarray sum of nums
        // case 2: target subarray = nums[0:i] and nums[j:n-1]
        // - answer2 = total sum - min subarray sum of nums
        const int n = nums.size();
        // dp[i][0] = min subarray sum of nums[0:i-1] ending at nums[i-1]
        // dp[i][1] = max subarray sum of nums[0:i-1] ending at nums[i-1]
        const int total = std::accumulate(nums.begin(), nums.end(), 0);
        std::vector<std::array<int, 2>> dp(n + 1, {0, 0});
        int max = INT_MIN;
        int min = INT_MAX;
        for (int i = 1; i <= n; ++i) {
            dp[i][0] = std::min(nums[i - 1], nums[i - 1] + dp[i - 1][0]);
            dp[i][1] = std::max(nums[i - 1], nums[i - 1] + dp[i - 1][1]);
            min = std::min(min, dp[i][0]);
            max = std::max(max, dp[i][1]);
        }
        if (total == min)
            return max; // empty subarray is not allowed

        return std::max(max, total - min);
    }
};