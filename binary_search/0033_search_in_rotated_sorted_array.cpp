#include <vector>

/**
 * There is an integer array nums sorted in ascending order (with distinct values).
 *
 * Prior to being passed to your function, nums is possibly rotated at an unknown pivot index k (1
 * <= k < nums.length) such that the resulting array is [nums[k], nums[k+1], ..., nums[n-1],
 * nums[0], nums[1], ..., nums[k-1]] (0-indexed). For example, [0,1,2,4,5,6,7] might be rotated at
 * pivot index 3 and become [4,5,6,7,0,1,2].
 *
 * Given the array nums after the possible rotation and an integer target, return the index of
 * target if it is in nums, or -1 if it is not in nums.
 *
 * You must write an algorithm with O(log n) runtime complexity.
 *
 * ! 1 <= nums.length <= 5000
 * ! -10^4 <= nums[i] <= 10^4
 * ! All values of nums are unique.
 * ! nums is an ascending array that is possibly rotated.
 * ! -10^4 <= target <= 10^4
 */

class Solution
{
public:
    int search(std::vector<int>& nums, int target)
    {
        if (nums.empty())
            return -1;

        int left = 0;
        int right = nums.size() - 1;
        while (left <= right) {
            if (nums[left] == target)
                return left;

            if (nums[right] == target)
                return right;

            int mid = left + (right - left) / 2;
            if (nums[mid] == target)
                return mid;

            // actually, we don't need to care about nums[mid] == nums[left],
            // because all elements are unique
            if (nums[mid] >= nums[left]) {
                // mid is in the left part
                // [LEFT...M...][...RIGHT]
                // | case1 |    case2    |
                if (target < nums[mid] && target > nums[left]) {
                    right = mid - 1;
                } else {
                    left = mid + 1;
                }
            } else {
                // mid is in the right part
                // [LEFT...][...M...RIGHT]
                // |    case2   |  case1 |
                if (target > nums[mid] && target < nums[right]) {
                    left = mid + 1;
                } else {
                    right = mid - 1;
                }
            }
        }
        return -1;
    }
};