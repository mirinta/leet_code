#include <vector>

/**
 * You are given a 0-indexed integer array nums, and an integer k.
 *
 * The K-or of nums is a non-negative integer that satisfies the following:
 *
 * The ith bit is set in the K-or if and only if there are at least k elements of nums in which bit
 * i is set. Return the K-or of nums.
 *
 * Note that a bit i is set in x if (2^i AND x) == 2^i, where AND is the bitwise AND operator.
 *
 * ! 1 <= nums.length <= 50
 * ! 0 <= nums[i] < 2^31
 * ! 1 <= k <= nums.length
 */

class Solution {
public:
    int findKOr(std::vector<int>& nums, int k)
    {
        int result = 0;
        for (int i = 0; i < 32; ++i) {
            int count = 0;
            for (const auto& val : nums) {
                count += (val >> i) & 1;
            }
            if (count >= k) {
                result |= 1 << i;
            }
        }
        return result;
    }
};