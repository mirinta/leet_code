#include <vector>

/**
 * You are given an integer array nums where the largest integer is unique.
 *
 * Determine whether the largest element in the array is at least twice as much as every other
 * number in the array. If it is, return the index of the largest element, or return -1 otherwise.
 *
 * ! 2 <= nums.length <= 50
 * ! 0 <= nums[i] <= 100
 * ! The largest element in nums is unique.
 */

class Solution {
public:
    int dominantIndex(const std::vector<int>& nums)
    {
        if (nums.size() < 2)
            return -1;

        int indexOfMaxVal = 0;
        for (int i = 0; i < nums.size(); ++i) {
            if (nums[i] > nums[indexOfMaxVal]) {
                indexOfMaxVal = i;
            }
        }
        for (int i = 0; i < nums.size(); ++i) {
            if (i == indexOfMaxVal)
                continue;

            if (nums[i] > nums[indexOfMaxVal] - nums[i])
                return -1;
        }
        return indexOfMaxVal;
    }
};