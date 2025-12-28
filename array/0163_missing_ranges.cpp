#include <vector>

/**
 * You are given an inclusive range [lower, upper] and a sorted unique integer array "nums", where
 * all elements are within the inclusive range.
 *
 * A number x is considered missing if x is in the range [lower, upper] and x is not in nums.
 *
 * Return the shortest sorted list of ranges that exactly covers all the missing numbers. That is,
 * no element of nums is included in any of the ranges, and each missing number is covered by one of
 * the ranges.
 *
 * ! -10^9 <= lower <= upper <= 10^9
 * ! 0 <= nums.length <= 100
 * ! lower <= nums[i] <= upper
 * ! All the values of nums are unique.
 */

class Solution {
public:
    std::vector<std::vector<int>> findMissingRanges(std::vector<int>& nums, int lower, int upper)
    {
        if (lower > upper)
            return {};

        const int n = nums.size();
        if (n == 0)
            return {{lower, upper}};

        std::vector<std::vector<int>> result;
        if (nums.front() > lower) {
            result.push_back({lower, nums.front() - 1});
        }
        for (int i = 1; i < n; ++i) {
            if (nums[i] - nums[i - 1] > 1) {
                result.push_back({nums[i - 1] + 1, nums[i] - 1});
            }
        }
        if (nums.back() < upper) {
            result.push_back({nums.back() + 1, upper});
        }
        return result;
    }
};
