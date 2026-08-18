#include <algorithm>
#include <unordered_map>
#include <vector>

/**
 * You are given an integer array nums and an integer k.
 *
 * An integer x is almost missing from nums if x appears in exactly one subarray of size k within nums.
 *
 * Return the largest almost missing integer from nums. If no such integer exists, return -1.
 *
 * A subarray is a contiguous sequence of elements within an array.
 *
 * ! 1 <= nums.length <= 50
 * ! 0 <= nums[i] <= 50
 * ! 1 <= k <= nums.length
 */

class Solution {
public:
    int largestInteger(std::vector<int>& nums, int k)
    {
        if (k == nums.size())
            return *std::max_element(nums.begin(), nums.end());

        std::unordered_map<int, int> map;
        for (const auto& v : nums) {
            map[v]++;
        }
        int result = -1;
        if (k == 1) {
            for (const auto& [val, freq] : map) {
                if (freq == 1) {
                    result = std::max(result, val);
                }
            }
            return result;
        }
        if (map[nums.front()] == 1) {
            result = std::max(result, nums.front());
        }
        if (map[nums.back()] == 1) {
            result = std::max(result, nums.back());
        }
        return result;
    }
};