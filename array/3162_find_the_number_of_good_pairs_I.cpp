#include <vector>

/**
 * You are given 2 integer arrays nums1 and nums2 of lengths n and m respectively. You are also
 * given a positive integer k.
 *
 * A pair (i, j) is called good if nums1[i] is divisible by nums2[j] * k (0 <= i <= n - 1, 0 <= j <=
 * m - 1).
 *
 * Return the total number of good pairs.
 *
 * ! 1 <= n, m <= 50
 * ! 1 <= nums1[i], nums2[j] <= 50
 * ! 1 <= k <= 50
 */

class Solution {
public:
    int numberOfPairs(std::vector<int>& nums1, std::vector<int>& nums2, int k)
    {
        int result = 0;
        for (const auto& val1 : nums1) {
            for (const auto& val2 : nums2) {
                if (val1 % (val2 * k) == 0) {
                    result++;
                }
            }
        }
        return result;
    }
};