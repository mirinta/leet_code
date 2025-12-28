#include <unordered_map>
#include <vector>

/**
 * You are given a 0-indexed integer array nums and an integer k.
 *
 * A subarray is called equal if all of its elements are equal. Note that the empty subarray is an
 * equal subarray.
 *
 * Return the length of the longest possible equal subarray after deleting at most k elements from
 * nums.
 *
 * A subarray is a contiguous, possibly empty sequence of elements within an array.
 *
 * ! 1 <= nums.length <= 10^5
 * ! 1 <= nums[i] <= nums.length
 * ! 0 <= k <= nums.length
 */

class Solution {
public:
    int longestEqualSubarray(std::vector<int>& nums, int k)
    {
        const int n = nums.size();
        std::unordered_map<int, std::vector<int>> map; // value to {i1,i2,...} s.t. nums[i] = value
        for (int i = 0; i < n; ++i) {
            map[nums[i]].push_back(i);
        }
        int result = 0;
        for (const auto& [val, positions] : map) {
            for (int left = 0, right = 0; right < positions.size(); ++right) {
                // num of consecutive equal elements = right - left + 1
                // total length = pos[right] - pos[left] + 1
                // num of removed elements = total length - num of consecutive equal elements
                while ((positions[right] - positions[left] + 1) - (right - left + 1) > k) {
                    left++;
                }
                result = std::max(result, right - left + 1);
            }
        }
        return result;
    }
};