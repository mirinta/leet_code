#include <vector>

/**
 * You are given an array nums1 of n distinct integers.
 *
 * You want to construct another array nums2 of length such that the elements in nums2 are either all odd or all even.
 *
 * For each index i, you must choose exactly one of the following (in any order):
 *
 * - nums2[i] = nums1[i]
 *
 * - nums2[i] = nums1[i] - nums1[j], for an index j != i
 *
 * Return true if it is impossible to construct such an array, otherwise, return false.
 *
 * ! 1 <= n == nums1.length <= 100
 * ! 1 <= nums1[i] <= 100
 * ! nums1 consists of distinct integers.
 */

class Solution {
public:
    bool uniformArray(std::vector<int>& nums1)
    {
        // if the elements are both odd or both even, then ans = true
        // otherwise, there exists at least one odd and at one even number,
        // then we can always create an odd number based on the given operations
        return true;
    }
};