#include <vector>

/**
 * You are given an integer array nums of length n and an integer k.
 *
 * You need to choose exactly k non-empty subarrays nums[l..r] of nums. Subarrays may overlap, and the exact same
 * subarray (same l and r) can be chosen more than once.
 *
 * The value of a subarray nums[l..r] is defined as: max(nums[l..r]) - min(nums[l..r]).
 *
 * The total value is the sum of the values of all chosen subarrays.
 *
 * Return the maximum possible total value you can achieve.
 *
 * ! 1 <= n == nums.length <= 5 * 10^4
 * ! 0 <= nums[i] <= 10^9
 * ! 1 <= k <= 10^5
 */

class Solution {
public:
    long long maxTotalValue(std::vector<int>& nums, int k)
    {
        int min = INT_MAX;
        int max = INT_MIN;
        for (const auto& v : nums) {
            min = std::min(min, v);
            max = std::max(max, v);
        }
        return 1LL * (max - min) * k;
    }
};