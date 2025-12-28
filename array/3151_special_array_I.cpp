#include <vector>

/**
 * An array is considered special if every pair of its adjacent elements contains two numbers with
 * different parity.
 *
 * You are given an array of integers nums. Return true if nums is a special array, otherwise,
 * return false.
 *
 * ! 1 <= nums.length <= 100
 * ! 1 <= nums[i] <= 100
 */

class Solution {
public:
    bool isArraySpecial(std::vector<int>& nums)
    {
        const int n = nums.size();
        for (int i = 0; i + 1 < n; ++i) {
            if (nums[i] % 2 == nums[i + 1] % 2)
                return false;
        }
        return true;
    }
};