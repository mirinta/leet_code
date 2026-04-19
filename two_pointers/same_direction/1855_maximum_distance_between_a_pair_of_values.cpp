#include <vector>

/**
 * You are given two non-increasing 0-indexed integer arrays nums1​​​​​​ and nums2​​​​​​.
 *
 * A pair of indices (i, j), where 0 <= i < nums1.length and 0 <= j < nums2.length, is valid if both i <= j and nums1[i]
 * <= nums2[j]. The distance of the pair is j - i​​​​.
 *
 * Return the maximum distance of any valid pair (i, j). If there are no valid pairs, return 0.
 *
 * An array arr is non-increasing if arr[i-1] >= arr[i] for every 1 <= i < arr.length.
 *
 * ! 1 <= nums1.length, nums2.length <= 10^5
 * ! 1 <= nums1[i], nums2[j] <= 10^5
 * ! Both nums1 and nums2 are non-increasing.
 */

class Solution {
public:
    int maxDistance(std::vector<int>& nums1, std::vector<int>& nums2)
    {
        return approach2(nums1, nums2);
    }

private:
    int approach2(const std::vector<int>& nums1, const std::vector<int>& nums2)
    {
        const int n1 = nums1.size();
        const int n2 = nums2.size();
        int i = 0;
        int j = 0;
        int result = 0;
        while (i < n1 && j < n2) {
            if (nums1[i] > nums2[j]) {
                i++;
            } else {
                result = std::max(result, j - i);
                j++;
            }
        }
        return result;
    }

    int approach1(const std::vector<int>& nums1, const std::vector<int>& nums2)
    {
        const int n1 = nums1.size();
        const int n2 = nums2.size();
        int result = 0;
        for (int i = 0; i < n1; ++i) {
            const int j = find(i, n2 - 1, nums1[i], nums2);
            if (j != -1) {
                result = std::max(result, j - i);
            }
        }
        return result;
    }

    int find(int lowerBound, int upperBound, int target, const std::vector<int>& nums)
    {
        if (lowerBound > upperBound)
            return -1;

        int lo = lowerBound;
        int hi = upperBound;
        while (lo <= hi) {
            const int mid = lo + (hi - lo) / 2;
            if (nums[mid] >= target) {
                lo = mid + 1;
            } else {
                hi = mid - 1;
            }
        }
        return hi < lowerBound ? -1 : hi;
    }
};