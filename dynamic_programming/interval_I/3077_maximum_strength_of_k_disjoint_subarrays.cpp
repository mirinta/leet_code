#include <array>
#include <vector>

/**
 * You are given a 0-indexed array of integers nums of length n, and a positive odd integer k.
 *
 * The strength of x subarrays is defined as strength = sum[1] * x - sum[2] * (x - 1) + sum[3] * (x
 * - 2) - sum[4] * (x - 3) + ... + sum[x] * 1 where sum[i] is the sum of the elements in the ith
 * subarray. Formally, strength is sum of (-1)^i+1 * sum[i] * (x - i + 1) over all i's such that 1
 * <= i <= x.
 *
 * You need to select k disjoint subarrays from nums, such that their strength is maximum.
 *
 * Return the maximum possible strength that can be obtained.
 *
 * Note that the selected subarrays don't need to cover the entire array.
 *
 * ! 1 <= n <= 10^4
 * ! -10^9 <= nums[i] <= 10^9
 * ! 1 <= k <= n
 * ! 1 <= n * k <= 10^6
 * ! k is odd.
 */

class Solution {
public:
    long long maximumStrength(std::vector<int>& nums, int k)
    {
        return approach2(nums, k);
    }

private:
    using LL = long long;

    long long approach2(const std::vector<int>& nums, int k)
    {
        const int n = nums.size();
        std::vector<std::array<LL, 2>> dp(k + 1, {LLONG_MIN / 2, LLONG_MIN / 2});
        dp[0][0] = 0;
        std::vector<std::array<LL, 2>> prev(k + 1);
        for (int i = 1; i <= n; ++i) {
            prev.assign(dp.begin(), dp.end());
            std::fill(dp.begin(), dp.end(), std::array<LL, 2>{LLONG_MIN / 2, LLONG_MIN / 2});
            dp[0][0] = 0;
            for (int j = 1; j <= k; ++j) {
                // case 1: nums[i-1] is not picked
                dp[j][0] = std::max(prev[j][0], prev[j][1]);
                // case 2: nums[i-1] is picked
                const LL sign = j & 1 ? 1 : -1;
                // case 2.1: nums[i-1] starts a new subarray
                const LL case1 = std::max(prev[j - 1][0], prev[j - 1][1]) + sign * nums[i - 1] * (k - j + 1);
                // case 2.2: nums[i-1] belongs to the previous subarray, nums[i-2] must be picked
                const LL case2 = prev[j][1] + sign * nums[i - 1] * (k - j + 1);
                dp[j][1] = std::max(case1, case2);
            }
        }
        return std::max(dp[k][0], dp[k][1]);
    }

    long long approach1(const std::vector<int>& nums, int k)
    {
        // dp[i][j][0] = max strength of j subarrays of nums[0:i-1] ending at nums[i-1] and
        // nums[i-1] is not picked
        // dp[i][j][1] = max strength of j subarrays of nums[0:i-1] ending at nums[i-1] and
        // nums[i-1] is picked
        // base cases:
        // dp[i>=0][0][0] = 0, select zero subarrays
        // dp[i>=0][0][1] = dp[0][j>0][0] = dp[0][j>0][1] = -INF, invalid cases
        const int n = nums.size();
        std::vector<std::vector<std::array<LL, 2>>> dp(
            n + 1, std::vector<std::array<LL, 2>>(k + 1, {LLONG_MIN / 2, LLONG_MIN / 2}));
        for (int i = 0; i <= n; ++i) {
            dp[i][0][0] = 0;
        }
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= k; ++j) {
                // case 1: nums[i-1] is not picked
                dp[i][j][0] = std::max(dp[i - 1][j][0], dp[i - 1][j][1]);
                // case 2: nums[i-1] is picked
                const LL sign = j & 1 ? 1 : -1;
                // case 2.1: nums[i-1] starts a new subarray
                const LL case1 = std::max(dp[i - 1][j - 1][0], dp[i - 1][j - 1][1]) + sign * nums[i - 1] * (k - j + 1);
                // case 2.2: nums[i-1] belongs to the previous subarray, nums[i-2] must be picked
                const LL case2 = dp[i - 1][j][1] + sign * nums[i - 1] * (k - j + 1);
                dp[i][j][1] = std::max(case1, case2);
            }
        }
        return std::max(dp[n][k][0], dp[n][k][1]);
    }
};