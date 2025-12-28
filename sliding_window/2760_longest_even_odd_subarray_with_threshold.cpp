#include <vector>

/**
 * You are given a 0-indexed integer array nums and an integer threshold.
 *
 * Find the length of the longest subarray of nums starting at index l and ending at index r (0 <= l
 * <= r < nums.length) that satisfies the following conditions:
 *
 * - nums[l] % 2 == 0
 *
 * - For all indices i in the range [l, r - 1], nums[i] % 2 != nums[i + 1] % 2
 *
 * - For all indices i in the range [l, r], nums[i] <= threshold
 * Return an integer denoting the length of the longest such subarray.
 *
 * Note: A subarray is a contiguous non-empty sequence of elements within an array.
 *
 * ! 1 <= nums.length <= 100
 * ! 1 <= nums[i] <= 100
 * ! 1 <= threshold <= 100
 */

class Solution {
public:
    int longestAlternatingSubarray(std::vector<int>& nums, int threshold)
    {
        int result = 0;
        int left = 0;
        int right = 0;
        bool flag = 0; // 0 for even, 1 for odd
        while (left < nums.size()) {
            if (nums[left] % 2 != 0 || nums[left] > threshold) {
                left++;
                continue;
            }
            right = left;
            flag = 0;
            while (right < nums.size() && nums[right] % 2 == flag && nums[right] <= threshold) {
                flag = !flag;
                right++;
            }
            result = std::max(result, right - left);
            left = right;
        }
        return result;
    }
};