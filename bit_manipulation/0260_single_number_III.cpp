#include <vector>

/**
 * Given an integer array nums, in which exactly two elements appear only once and all the other
 * elements appear exactly twice. Find the two elements that appear only once. You can return the
 * answer in any order.
 *
 * You must write an algorithm that runs in linear runtime complexity and uses only constant extra
 * space.
 *
 * ! 2 <= nums.length <= 3 * 10^4
 * ! -2^31 <= nums[i] <= 2^31 - 1
 * ! Each integer in nums will appear twice, only two integers will appear once.
 */

class Solution {
public:
    std::vector<int> singleNumber(std::vector<int>& nums)
    {
        long long XOR = 0;
        for (const auto& val : nums) {
            XOR ^= val;
        }
        // a and b must be different
        // XOR = a ^ b != 0, XOR has at least one bit of 1
        // lowbit = XOR & (-XOR), it is the rightmost set bit of XOR
        // assume lowbit[k] = 1, A[k] = 1 and B[k] = 0
        // use lowbit to divide nums into two groups
        // group1 = {A, x1, x1, x2, x2, ...}, where A[k] = xi[k] = 1
        // group2 = {B, y1, y1, y2, y2, ...}, where B[k] = yi[k] = 0
        long long lowbit = XOR & (-XOR);
        long long A = 0;
        long long B = 0;
        for (const auto& val : nums) {
            if (lowbit & val) {
                A ^= val;
            } else {
                B ^= val;
            }
        }
        return {static_cast<int>(A), static_cast<int>(B)};
    }
};