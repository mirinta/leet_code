#include <algorithm>
#include <vector>

/**
 * Given an integer array nums and an integer k, return the smallest positive multiple of k that ismissing from nums.
 *
 * A multiple of k is any positive integer divisible by k.
 *
 * ! 1 <= nums.length <= 100
 * ! 1 <= nums[i] <= 100
 * ! 1 <= k <= 100
 */

class Solution {
public:
    int missingMultiple(std::vector<int>& nums, int k)
    {
        const int max = *std::max_element(nums.begin(), nums.end());
        std::vector<int> missing(max / k + 2, true);
        for (const auto& val : nums) {
            if (val % k)
                continue;

            missing[val / k] = false;
        }
        for (int i = 1; i < missing.size(); ++i) {
            if (missing[i])
                return i * k;
        }
        return -1;
    }
};