#include <algorithm>
#include <vector>

/**
 * You are given two integer arrays nums1 and nums2.
 *
 * From nums1 two elements have been removed, and all other elements have been increased (or
 * decreased in the case of negative) by an integer, represented by the variable x.
 *
 * As a result, nums1 becomes equal to nums2. Two arrays are considered equal when they contain the
 * same integers with the same frequencies.
 *
 * Return the minimum possible integer x that achieves this equivalence.
 *
 * ! 3 <= nums1.length <= 200
 * ! nums2.length == nums1.length - 2
 * ! 0 <= nums1[i], nums2[i] <= 1000
 * ! The test cases are generated in a way that there is an integer x such that nums1 can become
 * ! equal to nums2 by removing two elements and adding x to each element of nums1.
 */

class Solution {
public:
    int minimumAddedInteger(std::vector<int>& nums1, std::vector<int>& nums2)
    {
        // remove 2 elements from nums1 => nums1'
        // then x = nums2.min - nums1'.min
        // there are only 3 cases of nums1'.min:
        // - nums1'.min = the 1st min element of the original nums1
        // - nums1'.min = the 2nd min element of the original nums1
        // - nums1'.min = the 3rd min element of the original nums1
        const int n = nums1.size();
        std::sort(nums1.begin(), nums1.end());
        std::sort(nums2.begin(), nums2.end());
        int result = INT_MAX;
        for (int i = 0; i <= 2; ++i) {
            const int x = nums2[0] - nums1[i];
            if (isValid(i, n - 1, x, nums1, nums2)) {
                result = std::min(result, x);
            }
        }
        return result;
    }

private:
    // check if nums2 is a subsequence of nums1[lo:hi] by adding x to each element of nums1[lo:hi]
    bool isValid(int lo, int hi, int x, const std::vector<int>& nums1, const std::vector<int>& nums2)
    {
        int i = lo;
        int j = 0;
        while (i <= hi) {
            if (nums1[i] + x == nums2[j]) {
                j++;
            }
            if (j == nums2.size())
                return true;

            i++;
        }
        return false;
    }
};