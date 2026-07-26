#include <vector>

/**
 * You are given an integer array nums of length n, where nums is a permutation of the numbers in the range [1, n].
 *
 * A XOR triplet is defined as the XOR of three elements nums[i] XOR nums[j] XOR nums[k] where i <= j <= k.
 *
 * Return the number of unique XOR triplet values from all possible triplets (i, j, k).
 *
 * ! 1 <= n == nums.length <= 10^5
 * ! 1 <= nums[i] <= n
 * ! nums is a permutation of integers from 1 to n.
 */

class Solution {
public:
    int uniqueXorTriplets(std::vector<int>& nums)
    {
        int n = nums.size();
        if (n < 3)
            return n;

        int result = 1;
        while (n) {
            n >>= 1;
            result <<= 1;
        }
        return result;
    }
};