#include <unordered_map>
#include <vector>

/**
 * You are given an integer array nums and an integer k.
 *
 * The frequency of an element x is the number of times it occurs in an array.
 *
 * An array is called good if the frequency of each element in this array is less than or equal to
 * k.
 *
 * Return the length of the longest good subarray of nums.
 *
 * A subarray is a contiguous non-empty sequence of elements within an array.
 *
 * ! 1 <= nums.length <= 10^5
 * ! 1 <= nums[i] <= 10^9
 * ! 1 <= k <= nums.length
 */

class Solution {
public:
    int maxSubarrayLength(std::vector<int>& nums, int k)
    {
        const int n = nums.size();
        std::unordered_map<int, int> map;
        int result = 0;
        for (int left = 0, right = 0; right < n; ++right) {
            map[nums[right]]++;
            while (map[nums[right]] > k) {
                map[nums[left]]--;
                left++;
            }
            result = std::max(result, right - left + 1);
        }
        return result;
    }
};