#include <vector>

/**
 * Given an array of positive integers nums, return the maximum possible sum of an ascending
 * subarray in nums.
 *
 * A subarray is defined as a contiguous sequence of numbers in an array.
 *
 * A subarray [numsl, numsl+1, ..., numsr-1, numsr] is ascending if for all i where l <= i < r,
 * numsi < numsi+1. Note that a subarray of size 1 is ascending.
 *
 * ! 1 <= nums.length <= 100
 * ! 1 <= nums[i] <= 100
 */

class Solution {
public:
    int maxAscendingSum(std::vector<int>& nums)
    {
        const int n = nums.size();
        int i = 0;
        int result = INT_MIN;
        while (i < n) {
            int j = i + 1;
            int sum = nums[i];
            while (j < n && nums[j] > nums[j - 1]) {
                sum += nums[j];
                j++;
            }
            result = std::max(result, sum);
            i = j;
        }
        return result;
    }
};