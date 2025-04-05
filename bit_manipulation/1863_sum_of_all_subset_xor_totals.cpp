#include <vector>

/**
 * The XOR total of an array is defined as the bitwise XOR of all its elements, or 0 if the array is
 * empty.
 *
 * For example, the XOR total of the array [2,5,6] is 2 XOR 5 XOR 6 = 1.
 * Given an array nums, return the sum of all XOR totals for every subset of nums.
 *
 * Note: Subsets with the same elements should be counted multiple times.
 *
 * An array a is a subset of an array b if a can be obtained from b by deleting some (possibly zero)
 * elements of b.
 *
 * ! 1 <= nums.length <= 12
 * ! 1 <= nums[i] <= 20
 */

class Solution
{
public:
    int subsetXORSum(std::vector<int>& nums)
    {
        const int n = nums.size();
        int result = 0;
        for (int mask = 0; mask < (1 << n); ++mask) {
            int XOR = 0;
            for (int i = 0; i < n; ++i) {
                if (mask >> i & 1) {
                    XOR ^= nums[i];
                }
            }
            result += XOR;
        }
        return result;
    }
};