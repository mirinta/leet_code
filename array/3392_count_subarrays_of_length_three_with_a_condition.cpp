#include <vector>

/**
 * Given an integer array nums, return the number of subarrays of length 3 such that the sum of the
 * first and third numbers equals exactly half of the second number.
 *
 * ! 3 <= nums.length <= 100
 * ! -100 <= nums[i] <= 100
 */

class Solution {
public:
    int countSubarrays(std::vector<int>& nums)
    {
        // nums[i-2] + nums[i] = nums[i-1] / 2
        // sum of nums[i-2:i] = 3 * (nums[i-2] + nums[i])
        const int n = nums.size();
        int result = 0;
        for (int i = 2; i < n; ++i) {
            if (nums[i - 1] == 2 * (nums[i] + nums[i - 2])) {
                result++;
            }
        }
        return result;
    }
};
