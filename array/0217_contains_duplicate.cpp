#include <unordered_map>
#include <vector>

/**
 * Given an integer array nums, return true if any value appears at least twice in the array, and
 * return false if every element is distinct.
 *
 * ! 1 <= nums.length <= 10^5
 * ! -10^9 <= nums[i] <= 10^9
 */

class Solution {
public:
    bool containsDuplicate(std::vector<int>& nums)
    {
        std::unordered_map<int, int> map;
        for (const auto& val : nums) {
            map[val]++;
            if (map[val] >= 2)
                return true;
        }
        return false;
    }
};