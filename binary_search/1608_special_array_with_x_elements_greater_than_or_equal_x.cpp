#include <algorithm>
#include <vector>

/**
 * You are given an array nums of non-negative integers. nums is considered special if there exists
 * a number x such that there are exactly x numbers in nums that are greater than or equal to x.
 *
 * Notice that x does not have to be an element in nums.
 *
 * Return x if the array is special, otherwise, return -1. It can be proven that if nums is special,
 * the value for x is unique.
 *
 * ! 1 <= nums.length <= 100
 * ! 0 <= nums[i] <= 1000
 */

class Solution {
public:
    int specialArray(std::vector<int>& nums)
    {
        const int n = nums.size();
        std::sort(nums.begin(), nums.end());
        for (int x = 1; x <= n; ++x) {
            const int i = std::lower_bound(nums.begin(), nums.end(), x) - nums.begin();
            if (n - i == x)
                return x;
        }
        return -1;
    }
};