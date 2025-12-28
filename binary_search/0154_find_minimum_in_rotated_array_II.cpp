#include <vector>

/**
 * Suppose an array of length "n" sorted in ascending order is rotated between 1 and n times. For
 * example, the array nums = [0,1,4,4,5,6,7] might become:
 *
 * - [4,5,6,7,0,1,4] if it was rotated 4 times.
 *
 * - [0,1,4,4,5,6,7] if it was rotated 7 times.
 *
 * Notice that rotating an array [a[0], a[1], a[2], ..., a[n-1]] 1 time results in the array
 * [a[n-1], a[0], a[1], a[2], ..., a[n-2]].
 *
 * Given the sorted rotated array nums that may contain duplicates, return the minimum element of
 * this array.
 *
 * You must decrease the overall operation steps as much as possible.
 *
 * ! n == nums.length
 * ! 1 <= n <= 5000
 * ! -5000 <= nums[i] <= 5000
 * ! nums is sorted and rotated between 1 and n times.
 */

class Solution {
public:
    int findMin(std::vector<int>& nums)
    {
        if (nums.size() == 1)
            return nums.front();

        // nums may contain duplicates
        // [LEFT...MAX][MIN...RIGHT]
        int left = 0;
        int right = nums.size() - 1;
        while (left < right) {
            const int mid = left + (right - left) / 2;
            if (nums[mid] > nums[right]) {
                // nums[mid] is in the left part, skip nums[LEFT:MID]
                left = mid + 1;
            } else if (nums[mid] < nums[right]) {
                // nums[mid] is in the right part
                right = mid; // not mid - 1, because nums[mid] may be the minimum element
            } else {
                // nums[mid] == nums[right], we can't determine which part contains nums[mid]
                // so we simply skip nums[right]
                right--;
            }
        }
        return nums[left];
    }
};
