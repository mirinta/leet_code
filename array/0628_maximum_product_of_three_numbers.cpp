#include <algorithm>
#include <vector>

/**
 * Given an integer array nums, find three numbers whose product is maximum and return the maximum
 * product.
 *
 * ! 3 <= nums.length <= 10^4
 * ! -1000 <= nums[i] <= 1000
 */

class Solution {
public:
    int maximumProduct(std::vector<int>& nums)
    {
        if (nums.size() == 3)
            return nums[0] * nums[1] * nums[2];

        const int n = nums.size();
        std::sort(nums.begin(), nums.end());
        const int case1 = nums[n - 1] * nums[n - 2] * nums[n - 3];
        const int case2 = nums[n - 1] * nums[0] * nums[1];
        return std::max(case1, case2);
    }
};