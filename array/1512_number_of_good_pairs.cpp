#include <unordered_map>
#include <vector>

/**
 * Given an array of integers nums, return the number of good pairs.
 *
 * A pair (i, j) is called good if nums[i] == nums[j] and i < j.
 *
 * ! 1 <= nums.length <= 100
 * ! 1 <= nums[i] <= 100
 */

class Solution {
public:
    // time O(N), space O(N)
    int numIdenticalPairs(std::vector<int>& nums)
    {
        std::unordered_map<int, int> map; // val to frequency
        for (const auto& val : nums) {
            map[val]++;
        }
        int result = 0;
        for (const auto& [val, freq] : map) {
            if (freq > 1) {
                result += freq * (freq - 1) / 2;
            }
        }
        return result;
    }
};