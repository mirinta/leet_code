#include <vector>

/**
 * You are given a sorted array nums of n non-negative integers and an integer maximumBit. You want
 * to perform the following query n times:
 *
 * 1. Find a non-negative integer k < 2maximumBit such that nums[0] XOR nums[1] XOR ... XOR
 * nums[nums.length-1] XOR k is maximized. k is the answer to the ith query.
 *
 * 2. Remove the last element from the current array nums.
 *
 * Return an array answer, where answer[i] is the answer to the ith query.
 *
 * ! nums.length == n
 * ! 1 <= n <= 10^5
 * ! 1 <= maximumBit <= 20
 * ! 0 <= nums[i] < 2^maximumBit
 * ! nums​​​ is sorted in ascending order.
 */

class Solution {
public:
    std::vector<int> getMaximumXor(std::vector<int>& nums, int maximumBit)
    {
        const int n = nums.size();
        std::vector<int> result(n);
        const int mask = (1 << maximumBit) - 1;
        int XOR = 0;
        for (int i = 0; i < n; ++i) {
            XOR ^= nums[i];
            result[i] = ~(XOR & mask) & mask;
        }
        std::reverse(result.begin(), result.end());
        return result;
    }
};