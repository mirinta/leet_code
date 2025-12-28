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

class Solution {
public:
    int search(std::vector<int>& nums, int target)
    {
        const int n = nums.size();
        int left = 0;
        int right = n - 1;
        while (left <= right) {
            const int mid = left + (right - left) / 2;
            if (nums[mid] == target)
                return mid;

            // no duplicate values
            if (nums[mid] >= nums[left]) {
                // LEFT ... MID-1 MID MID+1 ... MAX MIN...RIGHT
                // |<---case1-->|     |<--------case2-------->|
                if (target >= nums[left] && target < nums[mid]) {
                    right = mid - 1;
                } else {
                    left = mid + 1;
                }
            } else {
                // LEFT ... MAX MIN ... MID-1 MID MID+1 ... RIGHT
                // |<---------case1-------->|     |<---case2--->|
                if (target <= nums[right] && target > nums[mid]) {
                    left = mid + 1;
                } else {
                    right = mid - 1;
                }
            }
        }
        return -1;
    }
};