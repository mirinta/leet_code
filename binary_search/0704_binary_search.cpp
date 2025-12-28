#include <vector>

/**
 * Given an array of integers "nums" which is sorted in ascending order, and an integer "target",
 * write a function to search target in "nums". If "target" exists, then return its index.
 * Otherwise, return -1.
 *
 * You must write an algorithm with O(log n) runtime complexity.
 *
 * ! 1 <= nums.length <= 10^4
 * ! -10^4 < nums[i], target < 10^4
 * ! All the integers in nums are unique.
 * ! nums is sorted in ascending order.
 */

class Solution {
public:
    // time complexity: O(logN), space complexity: O(1)
    int search(const std::vector<int>& nums, int target)
    {
        if (nums.empty())
            return -1;

        int low = 0;
        int high = nums.size() - 1;
        while (low <= high) {
            const auto mid = low + (high - low) / 2;
            const auto& val = nums[mid];
            if (target == val)
                return mid;

            if (target > val) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
        return -1;
    }
};
