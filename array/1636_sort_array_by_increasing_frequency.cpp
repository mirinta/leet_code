#include <algorithm>
#include <unordered_map>
#include <vector>

/**
 * Given an array of integers nums, sort the array in increasing order based on the frequency of the
 * values. If multiple values have the same frequency, sort them in decreasing order.
 *
 * Return the sorted array.
 *
 * ! 1 <= nums.length <= 100
 * ! -100 <= nums[i] <= 100
 */

class Solution {
public:
    std::vector<int> frequencySort(std::vector<int>& nums)
    {
        std::unordered_map<int, int> map;
        for (const auto& val : nums) {
            map[val]++;
        }
        std::sort(nums.begin(), nums.end(), [&map](const auto& v1, const auto& v2) {
            if (map[v1] != map[v2])
                return map[v1] < map[v2];

            return v1 > v2;
        });
        return nums;
    }
};
