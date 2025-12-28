#include <vector>

/**
 * Given an array of integers "nums" sorted in non-decreasing order, find the starting and ending
 * position of a given "target" value.
 *
 * If "target" is not found in the array, return [-1, -1].
 *
 * You must write an algorithm with O(logN) runtime complexity.
 *
 * ! 0 <= nums.length <= 10^5
 * ! -10^9 <= nums[i] <= 10^9
 * ! nums is a non-decreasing array.
 * ! -10^9 <= target <= 10^9
 */

class Solution {
public:
    std::vector<int> searchRange(std::vector<int>& nums, int target)
    {
        return {findFirst(target, nums), findLast(target, nums)};
    }

private:
    // find index j such that nums[j] is the first element equal to target
    int findFirst(int target, const std::vector<int>& nums)
    {
        int lo = 0;
        int hi = nums.size() - 1;
        while (lo <= hi) {
            const int mid = lo + (hi - lo) / 2;
            if (nums[mid] >= target) {
                hi = mid - 1;
            } else {
                lo = mid + 1;
            }
        } // when the loop ends, lo = hi + 1
        return lo < nums.size() && nums[lo] == target ? lo : -1;
    }

    // find index j such that nums[j] is the last element equal to target
    int findLast(int target, const std::vector<int>& nums)
    {
        int lo = 0;
        int hi = nums.size() - 1;
        while (lo <= hi) {
            const int mid = lo + (hi - lo) / 2;
            if (nums[mid] <= target) {
                lo = mid + 1;
            } else {
                hi = mid - 1;
            }
        } // when the loop ends, lo = hi + 1
        return hi >= 0 && nums[hi] == target ? hi : -1;
    }
};