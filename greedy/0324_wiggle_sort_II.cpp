#include <algorithm>
#include <vector>

/**
 * Given an integer array nums, reorder it such that nums[0] < nums[1] > nums[2] < nums[3]....
 *
 * You may assume the input array always has a valid answer.
 *
 * ! 1 <= nums.length <= 5 * 10^4
 * ! 0 <= nums[i] <= 5000
 * ! It is guaranteed that there will be an answer for the given input nums.
 *
 * ! Follow Up: Can you do it in O(n) time and/or in-place with O(1) extra space?
 */

class Solution {
    void wiggleSort(std::vector<int>& nums)
    {
        const int n = nums.size();
        auto copy(nums);
        std::sort(copy.begin(), copy.end());
        for (int k = 0, i = (n - 1) / 2, j = n - 1; k < n; ++k) {
            if (k % 2 == 0) {
                nums[k] = copy[i--];
            } else {
                nums[k] = copy[j--];
            }
        }
    }
};