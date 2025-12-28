#include <vector>

/**
 * You are given a binary array nums.
 *
 * You can do the following operation on the array any number of times (possibly zero):
 *
 * - Choose any 3 consecutive elements from the array and flip all of them.
 *
 * Flipping an element means changing its value from 0 to 1, and from 1 to 0.
 *
 * Return the minimum number of operations required to make all elements in nums equal to 1. If it
 * is impossible, return -1.
 *
 * ! 3 <= nums.length <= 10^5
 * ! 0 <= nums[i] <= 1
 */

class Solution {
public:
    int minOperations(std::vector<int>& nums)
    {
        const int n = nums.size();
        int result = 0;
        for (int i = 0; i + 2 < n; ++i) {
            if (!nums[i]) {
                nums[i] ^= 1;
                nums[i + 1] ^= 1;
                nums[i + 2] ^= 1;
                result++;
            }
        }
        return nums[n - 1] && nums[n - 2] ? result : -1;
    }
};
