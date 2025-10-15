#include <vector>

/**
 * Given an array nums of n integers, your task is to find the maximum value of k for which there
 * exist two adjacent subarrays of length k each, such that both subarrays are strictly increasing.
 * Specifically, check if there are two subarrays of length k starting at indices a and b (a < b),
 * where:
 *
 * - Both subarrays nums[a..a + k - 1] and nums[b..b + k - 1] are strictly increasing.
 *
 * - The subarrays must be adjacent, meaning b = a + k.
 *
 * Return the maximum possible value of k.
 *
 * A subarray is a contiguous non-empty sequence of elements within an array.
 *
 * ! 2 <= nums.length <= 2 * 10^5
 * ! -10^9 <= nums[i] <= 10^9
 */

class Solution
{
public:
    int maxIncreasingSubarrays(std::vector<int>& nums)
    {
        const int n = nums.size();
        int result = 0;
        for (int i = 1, count1 = 1, count2 = 0; i < n; ++i) {
            if (nums[i] > nums[i - 1]) {
                count1++;
            } else {
                std::swap(count1, count2);
                count1 = 1;
            }
            result = std::max(result, std::min(count1, count2));
            result = std::max(result, std::max(count1, count2) / 2);
        }
        return result;
    }
};
