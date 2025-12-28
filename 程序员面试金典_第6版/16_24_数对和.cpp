#include <algorithm>
#include <unordered_map>
#include <vector>

/**
 * 设计一个算法，找出数组中两数之和为指定值的所有整数对。一个数只能属于一个数对。
 *
 * ! nums.length <= 100000
 * ! -10^5 <= nums[i], target <= 10^5
 */

class Solution {
public:
    std::vector<std::vector<int>> pairSums(std::vector<int>& nums, int target)
    {
        return approach2(nums, target);
    }

private:
    std::vector<std::vector<int>> approach2(std::vector<int>& nums, int target)
    {
        const int n = nums.size();
        std::sort(nums.begin(), nums.end());
        std::vector<std::vector<int>> result;
        int i = 0;
        int j = n - 1;
        while (i < j) {
            if (nums[i] + nums[j] == target) {
                result.push_back({nums[i++], nums[j--]});
            } else if (nums[i] + nums[j] > target) {
                j--;
            } else {
                i++;
            }
        }
        return result;
    }

    std::vector<std::vector<int>> approach1(const std::vector<int>& nums, int target)
    {
        std::unordered_map<int, int> map;
        std::vector<std::vector<int>> result;
        for (const auto& val : nums) {
            const int other = target - val;
            if (map[other] > 0) {
                result.push_back({val, other});
                map[other]--;
            } else {
                map[val]++;
            }
        }
        return result;
    }
};