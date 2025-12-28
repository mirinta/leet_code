#include <algorithm>
#include <unordered_map>
#include <vector>

/**
 * We define a harmonious array as an array where the difference between its maximum value and its
 * minimum value is exactly 1.
 *
 * Given an integer array nums, return the length of its longest harmonious subsequence among all
 * its possible subsequences.
 *
 * ! 1 <= nums.length <= 2 * 10^4
 * ! -10^9 <= nums[i] <= 10^9
 */

class Solution {
public:
    int findLHS(std::vector<int>& nums)
    {
        return approach2(nums);
    }

private:
    int approach2(const std::vector<int>& nums)
    {
        std::unordered_map<int, int> map;
        int result = 0;
        for (const auto& val : nums) {
            map[val]++;
            if (map.count(val - 1)) {
                result = std::max(result, map[val] + map[val - 1]);
            }
            if (map.count(val + 1)) {
                result = std::max(result, map[val] + map[val + 1]);
            }
        }
        return result;
    }

    int approach1(const std::vector<int>& nums)
    {
        std::unordered_map<int, int> map;
        for (const auto& val : nums) {
            map[val]++;
        }
        std::vector<int> unique;
        unique.reserve(map.size());
        for (const auto& [val, freq] : map) {
            unique.push_back(val);
        }
        std::sort(unique.begin(), unique.end());
        int result = 0;
        for (int i = 1; i < unique.size(); ++i) {
            if (unique[i] - 1 == unique[i - 1]) {
                result = std::max(result, map[unique[i]] + map[unique[i - 1]]);
            }
        }
        return result;
    }
};
