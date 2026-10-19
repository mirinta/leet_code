#include <numeric>
#include <vector>

/**
 * You are given a 0-indexed integer array nums and a target element target.
 *
 * A target index is an index i such that nums[i] == target.
 *
 * Return a list of the target indices of nums after sorting nums in non-decreasing order. If there are no target
 * indices, return an empty list. The returned list must be sorted in increasing order.
 *
 * ! 1 <= nums.length <= 100
 * ! 1 <= nums[i], target <= 100
 */

class Solution {
public:
    std::vector<int> targetIndices(std::vector<int>& nums, int target)
    {
        return approach2(nums, target);
    }

private:
    std::vector<int> approach2(std::vector<int>& nums, int target)
    {
        const int max = *std::max_element(nums.begin(), nums.end());
        if (target > max)
            return {};

        std::vector<int> count(max + 1, 0);
        for (const auto& val : nums) {
            count[val]++;
        }
        if (count[target] == 0)
            return {};

        std::vector<int> result(count[target]);
        const int start = std::accumulate(count.begin(), count.begin() + target, 0);
        std::iota(result.begin(), result.end(), start);
        return result;
    }

    std::vector<int> approach1(std::vector<int>& nums, int target)
    {
        const int n = nums.size();
        std::sort(nums.begin(), nums.end());
        std::vector<int> result;
        for (int i = 0; i < n; ++i) {
            if (nums[i] == target) {
                result.emplace_back(i);
            }
        }
        return result;
    }
};
