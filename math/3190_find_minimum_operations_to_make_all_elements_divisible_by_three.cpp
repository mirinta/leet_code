#include <vector>

/**
 * You are given an integer array nums. In one operation, you can add or subtract 1 from any element
 * of nums.
 *
 * Return the minimum number of operations to make all elements of nums divisible by 3.
 *
 * ! 1 <= nums.length <= 50
 * ! 1 <= nums[i] <= 50
 */

class Solution {
public:
    int minimumOperations(std::vector<int>& nums)
    {
        int result = 0;
        for (const auto& val : nums) {
            if (val % 3) {
                result++;
            }
        }
        return result;
    }
};
