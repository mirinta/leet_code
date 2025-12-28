#include <algorithm>
#include <vector>

/**
 * You are given a 0-indexed array nums and a non-negative integer k.
 *
 * In one operation, you can do the following:
 *
 * - Choose an index i that hasn't been chosen before from the range [0, nums.length - 1].
 *
 * - Replace nums[i] with any integer from the range [nums[i] - k, nums[i] + k].
 *
 * The beauty of the array is the length of the longest subsequence consisting of equal elements.
 *
 * Return the maximum possible beauty of the array nums after applying the operation any number of
 * times.
 *
 * Note that you can apply the operation to each index only once.
 *
 * A subsequence of an array is a new array generated from the original array by deleting some
 * elements (possibly none) without changing the order of the remaining elements.
 *
 * ! 1 <= nums.length <= 10^5
 * ! 0 <= nums[i], k <= 10^5
 */

class Solution {
public:
    int maximumBeauty(std::vector<int>& nums, int k)
    {
        const int n = nums.size();
        std::sort(nums.begin(), nums.end());
        int result = 0;
        for (int left = 0, right = 0; right < n; ++right) {
            // let x = nums[left] and y = nums[right]
            // intersection between [x-k,x+k] and [y-k,y+k]
            // then x+k >= y-k, y-x <= 2k
            while (nums[right] - nums[left] > 2 * k) {
                left++;
            }
            result = std::max(result, right - left + 1);
        }
        return result;
    }
};