#include <algorithm>
#include <vector>

/**
 * You are given an integer array nums.
 *
 * In one move, you may increase the value of any single element nums[i] by 1.
 *
 * Return the minimum total number of moves required so that all elements in nums become equal.
 *
 * ! 1 <= nums.length <= 100
 * ! 1 <= nums[i] <= 100
 */

class Solution {
public:
    int minMoves(std::vector<int>& nums)
    {
        const int max = *std::max_element(nums.begin(), nums.end());
        int result = 0;
        for (const auto& val : nums) {
            result += max - val;
        }
        return result;
    }
};
