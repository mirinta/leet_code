#include <algorithm>
#include <vector>

/**
 * The product sum of two equal-length arrays a and b is equal to the sum of a[i] * b[i] for all 0
 * <= i < a.length (0-indexed).
 *
 * - For example, if a = [1,2,3,4] and b = [5,2,3,1], the product sum would be 1*5 + 2*2 + 3*3 + 4*1
 * = 22.
 *
 * Given two arrays nums1 and nums2 of length n, return the minimum product sum if you are allowed
 * to rearrange the order of the elements in nums1.
 *
 * ! n == nums1.length == nums2.length
 * ! 1 <= n <= 10^5
 * ! 1 <= nums1[i], nums2[i] <= 100
 */

class Solution
{
public:
    int minProductSum(std::vector<int>& nums1, std::vector<int>& nums2)
    {
        const int n = nums1.size();
        std::sort(nums1.begin(), nums1.end());
        std::sort(nums2.begin(), nums2.end(), std::greater<>());
        int result = 0;
        for (int i = 0; i < n; ++i) {
            result += nums1[i] * nums2[i];
        }
        return result;
    }
};