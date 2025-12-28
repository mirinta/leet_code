#include <algorithm>
#include <vector>

/**
 * You are given an integer array nums of size n.
 *
 * Consider a non-empty subarray from nums that has the maximum possible bitwise AND.
 *
 * - In other words, let k be the maximum value of the bitwise AND of any subarray of nums. Then,
 * only subarrays with a bitwise AND equal to k should be considered.
 *
 * Return the length of the longest such subarray.
 *
 * The bitwise AND of an array is the bitwise AND of all the numbers in it.
 *
 * A subarray is a contiguous sequence of elements within an array.
 *
 * ! 1 <= nums.length <= 10^5
 * ! 1 <= nums[i] <= 10^6
 */

class Solution {
public:
    int longestSubarray(std::vector<int>& nums)
    {
        // longest subarray that all elements are equal to max
        const int n = nums.size();
        const int max = *std::max_element(nums.begin(), nums.end());
        int i = 0;
        int result = 0;
        while (i < n) {
            while (i < n && nums[i] != max) {
                i++;
            }
            int j = i + 1;
            while (j < n && nums[j] == max) {
                j++;
            }
            result = std::max(result, j - i);
            i = j;
        }
        return result;
    }
};
