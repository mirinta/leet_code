#include <vector>

/**
 * Given a sorted array of distinct integers and a target value, return the index if the target is
 * found. If not, return the index where it would be if it were inserted in order.
 *
 * You must write an algorithm with O(logN) runtime complexity.
 *
 * ! 1 <= nums.length <= 10^4
 * ! -10^4 <= nums[i] <= 10^4
 * ! nums contains distinct values sorted in ascending order.
 * ! -10^4 <= target <= 10^4
 */

class Solution {
public:
    int searchInsert(std::vector<int>& nums, int target)
    {
        int lo = 0;
        int hi = nums.size() - 1;
        while (lo <= hi) {
            const int mid = lo + (hi - lo) / 2;
            if (nums[mid] == target)
                return mid; // the problem guarantees that nums contains distinct values

            // find index i such that nums[i] is the first element > target
            if (nums[mid] > target) {
                hi = mid - 1;
            } else {
                lo = mid + 1;
            }
        } // when the loop ends, lo = hi + 1
        return lo;
    }
};