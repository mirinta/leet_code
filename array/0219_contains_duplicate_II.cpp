#include <unordered_map>
#include <vector>

/**
 * Given an integer array nums and an integer k, return true if there are two distinct indices i and
 * j in the array such that nums[i] == nums[j] and abs(i - j) <= k.
 *
 * ! 1 <= nums.length <= 10^5
 * ! -10^9 <= nums[i] <= 10^9
 * ! 0 <= k <= 10^5
 */

class Solution {
public:
    bool containsNearbyDuplicate(std::vector<int>& nums, int k)
    {
        const int n = nums.size();
        std::unordered_map<int, int> map;
        for (int i = 0; i < n; ++i) {
            if (map.count(nums[i]) && i - map[nums[i]] <= k)
                return true;

            map[nums[i]] = i;
        }
        return false;
    }
};