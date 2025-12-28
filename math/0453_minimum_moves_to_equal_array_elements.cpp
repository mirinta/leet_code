#include <algorithm>
#include <vector>

/**
 * Given an integer array nums of size n, return the minimum number of moves required to make all
 * array elements equal.
 *
 * In one move, you can increment n - 1 elements of the array by 1.
 *
 * ! n == nums.length
 * ! 1 <= nums.length <= 10^5
 * ! -10^9 <= nums[i] <= 10^9
 * ! The answer is guaranteed to fit in a 32-bit integer.
 */

class Solution {
public:
    int minMoves(std::vector<int>& nums)
    {
        // increase n-1 elements by 1 <=> decrease the remaining element by 1
        const int min = *std::min_element(nums.begin(), nums.end());
        int result = 0;
        for (const auto& val : nums) {
            result += val - min;
        }
        return result;
    }
};