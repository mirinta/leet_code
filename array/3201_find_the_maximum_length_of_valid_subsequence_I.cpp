#include <algorithm>
#include <vector>

/**
 * You are given an integer array nums.
 *
 * A subsequence sub of nums with length x is called valid if it satisfies:
 *
 * - (sub[0] + sub[1]) % 2 == (sub[1] + sub[2]) % 2 == ... == (sub[x - 2] + sub[x - 1]) % 2.
 *
 * Return the length of the longest valid subsequence of nums.
 *
 * A subsequence is an array that can be derived from another array by deleting some or no elements
 * without changing the order of the remaining elements.
 *
 * ! 2 <= nums.length <= 2 * 10^5
 * ! 1 <= nums[i] <= 10^7
 */

class Solution
{
public:
    int maximumLength(std::vector<int>& nums)
    {
        int case1 = 0; // {odd, odd, ...}
        int case2 = 0; // {even, even, ...}
        int case3 = 0; // {even, odd, even, odd, ...}
        int case4 = 0; // {odd, even, odd, even, ...}
        bool case3PrevOdd = true;
        bool case4PrevOdd = false;
        for (const auto& val : nums) {
            const bool isOdd = val % 2;
            case1 += isOdd;
            case2 += !isOdd;
            case3 += isOdd ^ case3PrevOdd;
            case4 += isOdd ^ case4PrevOdd;
            case3PrevOdd = isOdd;
            case4PrevOdd = isOdd;
        }
        return std::max({case1, case2, case3, case4});
    }
};
