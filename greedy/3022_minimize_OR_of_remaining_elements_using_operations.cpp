#include <vector>

/**
 * You are given a 0-indexed integer array nums and an integer k.
 *
 * In one operation, you can pick any index i of nums such that 0 <= i < nums.length - 1 and replace
 * nums[i] and nums[i + 1] with a single occurrence of nums[i] & nums[i + 1], where & represents the
 * bitwise AND operator.
 *
 * Return the minimum possible value of the bitwise OR of the remaining elements of nums after
 * applying at most k operations.
 *
 * ! 1 <= nums.length <= 10^5
 * ! 0 <= nums[i] < 2^30
 * ! 0 <= k < nums.length
 */

class Solution {
public:
    int minOrAfterOperations(std::vector<int>& nums, int k)
    {
        int result = 0; // at most 30 bits
        int mask = 0;   // mask[i] = whether the ith bit is concerned
        for (int bit = 29; bit >= 0; --bit) {
            mask |= 1 << bit;
            // check if all concerned bits can be changed to 0 with at most k operations
            // - if true, answer[i] = 0
            // - otherwise, answer[i] = 1
            int operations = 0;
            int AND = 0;
            for (const auto& x : nums) {
                if (AND) {
                    AND &= x & mask;
                    operations++;
                } else if (x & mask) {
                    AND = x & mask;
                }
            }
            operations += AND ? 1 : 0;
            if (operations > k) {
                result |= 1 << bit;
                mask ^= 1 << bit; // the ith bit is no longer concerned
            }
        }
        return result;
    }
};