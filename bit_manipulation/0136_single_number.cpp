#include <vector>

/**
 * Given a non-empty array of integers nums, every element appears twice except for one. Find that
 * single one.
 *
 * You must implement a solution with a linear runtime complexity and use only constant extra space.
 *
 * ! 1 <= nums.length <= 3 * 10^4
 * ! -3 * 10^4 <= nums[i] <= 3 * 10^4
 * ! Each element in the array appears twice except for one element which appears only once.
 */

class Solution {
public:
    int singleNumber(std::vector<int>& nums)
    {
        // a^a=0, 0^a=a, (a^b)^c=a^(b^c)
        int result = 0;
        for (const auto& val : nums) {
            result ^= val;
        }
        return result;
    }
};