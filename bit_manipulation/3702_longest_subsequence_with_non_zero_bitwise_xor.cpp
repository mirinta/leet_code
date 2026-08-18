#include <vector>

/**
 * You are given an integer array nums.
 *
 * Return the length of the longest subsequence in nums whose bitwise XOR is non-zero. If no such subsequence exists,
 * return 0.
 *
 * ! 1 <= nums.length <= 10^5
 * ! 0 <= nums[i] <= 10^9
 */

class Solution {
public:
    int longestSubsequence(std::vector<int>& nums)
    {
        const int n = nums.size();
        int XOR = 0;
        bool allZero = true;
        for (const auto& val : nums) {
            XOR ^= val;
            allZero &= val == 0;
        }
        if (XOR != 0)
            return n;

        // xor = 0:
        // case 1: all zero, ans = 0
        // case 2: at least one element x != 0,
        //         xor = remaining_xor ^ x = 0,
        //         means remaining_xor = x, ans = n-1
        return allZero ? 0 : n - 1;
    }
};