#include <vector>

/**
 * You are given a binary array nums.
 *
 * A subarray of an array is good if it contains exactly one element with the value 1.
 *
 * Return an integer denoting the number of ways to split the array nums into good subarrays. As the
 * number may be too large, return it modulo 10^9 + 7.
 *
 * A subarray is a contiguous non-empty sequence of elements within an array.
 *
 * ! 1 <= nums.length <= 10^5
 * ! 0 <= nums[i] <= 1
 */

class Solution {
public:
    int numberOfGoodSubarraySplits(std::vector<int>& nums)
    {
        // ...1 [] 0 [] 0 [] 0 [] 1...
        // count number of intervals between two adjacent 1's,
        // and apply multiplication principle
        constexpr int kMod = 1e9 + 7;
        int prevOne = -1;
        long long result = 1;
        for (int i = 0; i < nums.size(); ++i) {
            if (nums[i] == 0)
                continue;

            if (prevOne == -1) {
                prevOne = i;
            } else {
                result = result * (i - prevOne) % kMod;
                prevOne = i;
            }
        }
        return prevOne == -1 ? 0 : result;
    }
};