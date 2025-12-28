#include <algorithm>
#include <vector>

/**
 * Given an array nums sorted in non-decreasing order, return the maximum between the number of
 * positive integers and the number of negative integers.
 *
 * In other words, if the number of positive integers in nums is pos and the number of negative
 * integers is neg, then return the maximum of pos and neg. Note that 0 is neither positive nor
 * negative.
 *
 * ! 1 <= nums.length <= 2000
 * ! -2000 <= nums[i] <= 2000
 * ! nums is sorted in a non-decreasing order.
 *
 * ! Follow up: Can you solve the problem in O(log(n)) time complexity?
 */

class Solution {
public:
    int maximumCount(std::vector<int>& nums)
    {
        const int negative = std::lower_bound(nums.begin(), nums.end(), 0) - nums.begin();
        const int positive = nums.end() - std::upper_bound(nums.begin(), nums.end(), 0);
        return std::max(negative, positive);
    }
};