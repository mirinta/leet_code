#include <vector>

/**
 * Given two integer arrays nums1 and nums2, sorted in non-decreasing order, return the minimum
 * integer common to both arrays. If there is no common integer amongst nums1 and nums2, return -1.
 *
 * Note that an integer is said to be common to nums1 and nums2 if both arrays have at least one
 * occurrence of that integer.
 *
 * ! 1 <= nums1.length, nums2.length <= 10^5
 * ! 1 <= nums1[i], nums2[j] <= 10^9
 * ! Both nums1 and nums2 are sorted in non-decreasing order.
 */

class Solution {
public:
    int getCommon(std::vector<int>& nums1, std::vector<int>& nums2)
    {
        const int m = nums1.size();
        const int n = nums2.size();
        int i = 0;
        int j = 0;
        while (i < m && j < n) {
            if (nums1[i] == nums2[j])
                return nums1[i];

            if (nums1[i] < nums2[j]) {
                i++;
            } else {
                j++;
            }
        }
        return -1;
    }
};