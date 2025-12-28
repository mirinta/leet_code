#include <algorithm>
#include <vector>

/**
 * You are given a 0-indexed integer array nums, and an integer k.
 *
 * In one operation, you can remove one occurrence of the smallest element of nums.
 *
 * Return the minimum number of operations needed so that all elements of the array are greater than
 * or equal to k.
 *
 * ! 1 <= nums.length <= 50
 * ! 1 <= nums[i] <= 10^9
 * ! 1 <= k <= 10^9
 * ! The input is generated such that there is at least one index i such that nums[i] >= k.
 */

class Solution {
public:
    int minOperations(std::vector<int>& nums, int k)
    {
        return std::count_if(nums.begin(), nums.end(), [&k](const auto& val) { return val < k; });
    }
};