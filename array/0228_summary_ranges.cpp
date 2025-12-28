#include <string>
#include <vector>

/**
 * You are given a sorted unique integer array "nums".
 *
 * A range [a, b] is the set of all integers from a to b (inclusive).
 *
 * Return the smallest sorted list of ranges that cover all the numbers in the array exactly. That
 * is, each element of nums is covered by exactly one of the ranges, and there is no integer x such
 * that x is in one of the ranges but not in nums.
 *
 * Each range [a, b] in the list should be output as:
 *
 * - "a->b" if a != b
 *
 * - "a" if a == b
 *
 * ! 0 <= nums.length <= 20
 * ! -2^31 <= nums[i] <= 2^31 - 1
 * ! All the values of nums are unique.
 * ! nums is sorted in ascending order.
 */

class Solution {
public:
    std::vector<std::string> summaryRanges(std::vector<int>& nums)
    {
        if (nums.empty())
            return {};

        const int n = nums.size();
        std::vector<std::string> result;
        int i = 0;
        while (i < n) {
            int j = i + 1;
            while (j < n && nums[j - 1] + 1 == nums[j]) {
                j++;
            }
            if (j - 1 == i) {
                result.push_back(std::to_string(nums[i]));
            } else {
                result.push_back(std::to_string(nums[i]) + "->" + std::to_string(nums[j - 1]));
            }
            i = j;
        }
        return result;
    }
};
