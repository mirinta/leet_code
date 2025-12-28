#include <unordered_set>
#include <vector>

/**
 * Given an integer array nums that does not contain any zeros, find the largest positive integer k
 * such that -k also exists in the array.
 *
 * Return the positive integer k. If there is no such integer, return -1.
 *
 * ! 1 <= nums.length <= 1000
 * ! -1000 <= nums[i] <= 1000
 * ! nums[i] != 0
 */

class Solution {
public:
    int findMaxK(std::vector<int>& nums)
    {
        std::unordered_set<int> set;
        int result = -1;
        for (const auto& val : nums) {
            if (set.count(-val)) {
                result = std::max(result, std::abs(val));
            }
            set.insert(val);
        }
        return result;
    }
};