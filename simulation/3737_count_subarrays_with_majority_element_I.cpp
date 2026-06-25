#include <vector>

/**
 * You are given an integer array nums and an integer target.
 *
 * Return the number of subarrays of nums in which target is the majority element.
 *
 * The majority element of a subarray is the element that appears strictly more than half of the times in that subarray.
 *
 * ! 1 <= nums.length <= 1000
 * ! 1 <= nums[i] <= 10^9
 * ! 1 <= target <= 10^9
 */

class Solution {
public:
    int countMajoritySubarrays(std::vector<int>& nums, int target)
    {
        const int n = nums.size();
        int result = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = i, count = 0; j < n; ++j) {
                count += nums[j] == target;
                result += 2 * count > (j - i + 1);
            }
        }
        return result;
    }
};