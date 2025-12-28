#include <vector>

/**
 * Given an array of integers nums and an integer k, return the number of contiguous subarrays where
 * the product of all the elements in the subarray is strictly less than k.
 *
 * ! 1 <= nums.length <= 3 * 10^4
 * ! 1 <= nums[i] <= 1000
 * ! 0 <= k <= 10^6
 */

class Solution {
public:
    int numSubarrayProductLessThanK(std::vector<int>& nums, int k)
    {
        if (k <= 1)
            return 0;

        const int n = nums.size();
        int result = 0;
        for (int left = 0, right = 0, product = 1; right < n; ++right) {
            product *= nums[right];
            while (product >= k) {
                product /= nums[left];
                left++;
            }
            result += right - left + 1;
        }
        return result;
    }
};