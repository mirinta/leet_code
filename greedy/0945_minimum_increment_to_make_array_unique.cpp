#include <algorithm>
#include <vector>

/**
 * You are given an integer array nums. In one move, you can pick an index i where 0 <= i <
 * nums.length and increment nums[i] by 1.
 *
 * Return the minimum number of moves to make every value in nums unique.
 *
 * The test cases are generated so that the answer fits in a 32-bit integer.
 *
 * ! 1 <= nums.length <= 10^5
 * ! 0 <= nums[i] <= 10^5
 */

class Solution {
public:
    int minIncrementForUnique(std::vector<int>& nums)
    {
        std::sort(nums.begin(), nums.end());
        int result = 0;
        for (int i = 1; i < nums.size(); ++i) {
            if (nums[i] <= nums[i - 1]) {
                result += nums[i - 1] - nums[i] + 1;
                nums[i] = nums[i - 1] + 1;
            }
        }
        return result;
    }
};