#include <algorithm>
#include <vector>

/**
 * You are given an integer array nums of size n and a positive integer k.
 *
 * Divide the array into one or more arrays of size 3 satisfying the following conditions:
 *
 * - Each element of nums should be in exactly one array.
 *
 * - The difference between any two elements in one array is less than or equal to k.
 *
 * Return a 2D array containing all the arrays. If it is impossible to satisfy the conditions,
 * return an empty array. And if there are multiple answers, return any of them.
 *
 * ! n == nums.length
 * ! 1 <= n <= 10^5
 * ! n is a multiple of 3.
 * ! 1 <= nums[i] <= 10^5
 * ! 1 <= k <= 10^5
 */

class Solution {
public:
    std::vector<std::vector<int>> divideArray(std::vector<int>& nums, int k)
    {
        const int n = nums.size();
        std::sort(nums.begin(), nums.end());
        std::vector<std::vector<int>> result;
        for (int i = 0; i + 2 < n; i += 3) {
            if (nums[i + 2] - nums[i] > k)
                return {};

            result.emplace_back(nums.begin() + i, nums.begin() + i + 3);
        }
        return result;
    }
};