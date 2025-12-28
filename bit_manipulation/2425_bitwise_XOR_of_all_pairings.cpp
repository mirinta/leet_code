#include <vector>

/**
 * You are given two 0-indexed arrays, nums1 and nums2, consisting of non-negative integers. There
 * exists another array, nums3, which contains the bitwise XOR of all pairings of integers between
 * nums1 and nums2 (every integer in nums1 is paired with every integer in nums2 exactly once).
 *
 * Return the bitwise XOR of all integers in nums3.
 *
 * ! 1 <= nums1.length, nums2.length <= 10^5
 * ! 0 <= nums1[i], nums2[j] <= 10^9
 */

class Solution {
public:
    int xorAllNums(std::vector<int>& nums1, std::vector<int>& nums2)
    {
        const int m = nums1.size();
        const int n = nums2.size();
        int result = 0;
        for (int i = 0; i < m && n % 2; ++i) {
            result ^= nums1[i];
        }
        for (int i = 0; i < n && m % 2; ++i) {
            result ^= nums2[i];
        }
        return result;
    }
};
