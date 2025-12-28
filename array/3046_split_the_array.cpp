#include <unordered_map>
#include <vector>

/**
 * You are given an integer array nums of even length. You have to split the array into two parts
 * nums1 and nums2 such that:
 *
 * - nums1.length == nums2.length == nums.length / 2.
 *
 * - nums1 should contain distinct elements.
 *
 * - nums2 should also contain distinct elements.
 *
 * Return true if it is possible to split the array, and false otherwise.
 *
 * ! 1 <= nums.length <= 100
 * ! nums.length % 2 == 0
 * ! 1 <= nums[i] <= 100
 */

class Solution {
public:
    bool isPossibleToSplit(std::vector<int>& nums)
    {
        std::unordered_map<int, int> map;
        for (const auto& val : nums) {
            map[val]++;
            if (map[val] > 2)
                return false;
        }
        return true;
    }
};