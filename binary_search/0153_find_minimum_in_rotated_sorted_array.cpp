#include <vector>

/**
 * Suppose an array of length n sorted in ascending order is rotated between 1 and n times. For
 * example, the array nums = [0, 1, 2, 3, 4, 5, 6, 7] might become:
 *
 * - [4,5,6,7,0,1,2] if it was rotated 4 times.
 *
 * - [0,1,2,4,5,6,7] if it was rotated 7 times.
 *
 * Notice that rotating an array [a[0], a[1], a[2], ..., a[n-1]] 1 time results in the array
 * [a[n-1], a[0], a[1], a[2], ..., a[n-2]].
 *
 * Given the sorted rotated array nums of unique elements, return the minimum element of this array.
 *
 * You must write an algorithm that runs in O(log n) time.
 *
 * ! n == nums.length
 * ! 1 <= n <= 5000
 * ! -5000 <= nums[i] <= 5000
 * ! All the integers of nums are unique.
 * ! nums is sorted and rotated between 1 and n times.
 */

class Solution {
public:
    int findMin(std::vector<int>& nums)
    {
        // #NOTE# nums[i] are unique
        const int n = nums.size();
        if (n == 1 || nums.back() > nums.front())
            return nums.front();

        // if nums is rotated,
        // it becomes [LEFT...MAX MIN...RIGHT]
        //             |<-left->| |<-right->|
        // left part is increasing, and right part is increasing
        // the minimum element is in the right part
        int left = 0;
        int right = n - 1;
        while (left < right) {
            const int mid = left + (right - left) / 2;
            if (nums[mid] < nums[right]) {
                // [LEFT...MAX MIN...MID...RIGHT]
                // mid is in the right part
                right = mid; // not mid - 1, because nums[mid] may be the minimum element
            } else {
                // [LEFT...MID...MAX MIN...RIGHT]
                // mid is in the left part, skip nums[LEFT:MID]
                left = mid + 1;
            }
        }
        return nums[left];
    }
};
