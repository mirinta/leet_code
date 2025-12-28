#include <vector>

/**
 * There is an integer array nums sorted in non-decreasing order (not necessarily with distinct
 * values).
 *
 * Before being passed to your function, nums is rotated at an unknown pivot index k (0 <= k <
 * nums.length) such that the resulting array is [nums[k], nums[k+1], ..., nums[n-1], nums[0],
 * nums[1], ..., nums[k-1]] (0-indexed). For example, [0,1,2,4,4,4,5,6,6,7] might be rotated at
 * pivot index 5 and become [4,5,6,6,7,0,1,2,4,4].
 *
 * Given the array nums after the rotation and an integer target, return true if target is in nums,
 * or false if it is not in nums.
 *
 * You must decrease the overall operation steps as much as possible.
 *
 * ! 1 <= nums.length <= 5000
 * ! -10^4 <= nums[i] <= 10^4
 * ! nums is guaranteed to be rotated at some pivot.
 * ! -10^4 <= target <= 10^4
 */

class Solution {
public:
    bool search(std::vector<int>& nums, int target)
    {
        int left = 0;
        int right = nums.size() - 1;
        while (left <= right) {
            const int mid = left + (right - left) / 2;
            if (nums[mid] == target || nums[left] == target || nums[right] == target)
                return true;

            if (nums[mid] > nums[left]) {
                // [LEFT...M...][...RIGHT]
                // | case1 |   case2     |
                if (nums[mid] > target && target > nums[left]) {
                    right = mid - 1;
                } else {
                    left = mid + 1;
                }
            } else if (nums[mid] == nums[left]) {
                left++;
            } else if (nums[mid] == nums[right]) {
                right--;
            } else {
                // [LEFT...][...M...RIGHT]
                // |    case2   | case1  |
                if (nums[mid] < target && target < nums[right]) {
                    left = mid + 1;
                } else {
                    right = mid - 1;
                }
            }
        }
        return false;
    }
};