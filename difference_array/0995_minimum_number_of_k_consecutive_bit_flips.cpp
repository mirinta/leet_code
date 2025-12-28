#include <vector>

/**
 * You are given a binary array nums and an integer k.
 *
 * A k-bit flip is choosing a subarray of length k from nums and simultaneously changing every 0 in
 * the subarray to 1, and every 1 in the subarray to 0.
 *
 * Return the minimum number of k-bit flips required so that there is no 0 in the array. If it is
 * not possible, return -1.
 *
 * A subarray is a contiguous part of an array.
 *
 * ! 1 <= nums.length <= 10^5
 * ! 1 <= k <= nums.length
 */

class Solution {
public:
    int minKBitFlips(std::vector<int>& nums, int k)
    {
        // flips[i] = num of times that nums[i] is flipped
        // diff[i] = flips[i] - flips[i-1]
        const int n = nums.size();
        std::vector<int> diff(n, 0);
        int result = 0;
        for (int i = 0, flips = 0; i < n; ++i) {
            flips += diff[i];
            if ((flips % 2) ^ nums[i])
                continue;

            // we need to flip nums[i:i+k-1]
            if (i + k - 1 >= n)
                return -1;

            diff[i]++;
            if (i + k < n) {
                diff[i + k]--;
            }
            flips++;
            result++;
        }
        return result;
    }
};