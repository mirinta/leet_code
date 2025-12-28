#include <algorithm>
#include <vector>

/**
 * Given an integer array nums of size n, return the minimum number of moves required to make all
 * array elements equal.
 *
 * In one move, you can increment or decrement an element of the array by 1.
 *
 * Test cases are designed so that the answer will fit in a 32-bit integer.
 *
 * ! n == nums.length
 * ! 1 <= nums.length <= 10^5
 * ! -10^9 <= nums[i] <= 10^9
 */

class Solution {
public:
    int minMoves2(std::vector<int>& nums)
    {
        // change all elements to x
        // #moves = |nums[0]-x| + |nums[1]-x| + ... + |nums[n-1]-x|
        // #moves is minimized when x = median of nums
        // #moves = (x-nums[0]) + ... + (x-nums[mid-1]) + 0 + (nums[mid+1]-x) + ... + (nums[n-1]-x)
        const int n = nums.size();
        std::sort(nums.begin(), nums.end());
        const int median = nums[n / 2];
        int result = 0;
        for (const auto& val : nums) {
            result += std::abs(val - median);
        }
        return result;
    }
};