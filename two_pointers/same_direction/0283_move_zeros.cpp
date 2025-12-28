#include <vector>

/**
 * Given an integer array "nums", move all 0's to then end of it while maintaining the relative
 * order of the non-zero elements.
 *
 * Note that you must do this in-place without making a copy of the array.
 *
 * ! 1 <= nums.length <= 10^4
 * ! -2^31 <= nums[i] <= 2^31 - 1
 */

class Solution {
public:
    void moveZeroes(std::vector<int>& nums)
    {
        for (int i = 0, j = 0; j < nums.size(); ++j) {
            if (nums[j] != 0) {
                std::swap(nums[i], nums[j]);
                i++;
            }
        }
    }
};
