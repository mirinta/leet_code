#include <algorithm>
#include <vector>

/**
 * Given an integer array nums, reorder it such that nums[0] <= nums[1] >= nums[2] <= nums[3]....
 *
 * You may assume the input array always has a valid answer.
 *
 * ! 1 <= nums.length <= 5 * 10^4
 * ! 0 <= nums[i] <= 10^4
 * ! It is guaranteed that there will be an answer for the given input nums.
 */

class Solution {
public:
    void wiggleSort(std::vector<int>& nums)
    {
        return approach2(nums);
    }

private:
    // time O(N), space O(1)
    void approach2(std::vector<int>& nums)
    {
        // x0 <= x1 >= x2 <= x3 >= x4
        // if index i is even, we need nums[i] <= nums[i + 1]
        // - if not, swap(nums[i], nums[i + 1])
        // if i is odd, we need nums[i] >= nums[i + 1]
        // - if not, swap(nums[i], nums[i + 1])
        for (int i = 0; i < nums.size() - 1; ++i) {
            if (i % 2 == 0 && nums[i] > nums[i + 1]) {
                std::swap(nums[i], nums[i + 1]);
            } else if (i % 2 != 0 && nums[i] < nums[i + 1]) {
                std::swap(nums[i], nums[i + 1]);
            }
        }
    }

    // time O(NlogN), space O(1)
    void approach1(std::vector<int>& nums)
    {
        // x0 <= [x1 >= x2] <= [x3 >= x4]
        // if x2 >= x0 and x4 >= x1
        // we can rearrange it to an array in non-decreasing order
        // x0 <= [x2 <= x1] <= [x4 <= x3]
        // in other words, if we have an array in non-decreasing order,
        // we can swap(x1, x2), swap(x3, x4), ... to get the final answer
        std::sort(nums.begin(), nums.end());
        for (int i = 2; i < nums.size(); i += 2) {
            std::swap(nums[i], nums[i - 1]);
        }
    }
};
