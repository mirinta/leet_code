#include <vector>

/**
 * Given two sorted arrays nums1 and nums2 of size m and n respectively, return the median of the
 * two sorted arrays.
 *
 * The overall run time complexity should be O(log (m+n)).
 *
 * ! nums1.length == m
 * ! nums2.length == n
 * ! 0 <= m <= 1000
 * ! 0 <= n <= 1000
 * ! 1 <= m + n <= 2000
 * ! -10^6 <= nums1[i], nums2[i] <= 10^6
 */

class Solution {
public:
    double findMedianSortedArrays(std::vector<int>& nums1, std::vector<int>& nums2)
    {
        return approach3(nums1, nums2);
    }

private:
    double approach3(const std::vector<int>& nums1, const std::vector<int>& nums2)
    {
        // nums1: [left1][right1]
        // nums2: [left2][right2]
        // merge: [left1+lef2][right1+right2]
        // binary search the size of left1 = x
        // then the size of left2 = (m+n+1)/2 - x
        if (nums1.size() > nums2.size())
            return approach3(nums2, nums1);

        const int m = nums1.size();
        const int n = nums2.size();
        int lo = 0;
        int hi = m;
        while (lo <= hi) {
            const int cut1 = lo + (hi - lo) / 2;
            const int cut2 = (m + n + 1) / 2 - cut1;
            const int leftMax1 = cut1 == 0 ? INT_MIN : nums1[cut1 - 1];
            const int rightMin1 = cut1 == m ? INT_MAX : nums1[cut1];
            const int leftMax2 = cut2 == 0 ? INT_MIN : nums2[cut2 - 1];
            const int rightMin2 = cut2 == n ? INT_MAX : nums2[cut2];
            const int leftMax = std::max(leftMax1, leftMax2);
            const int rightMin = std::min(rightMin1, rightMin2);
            if (leftMax <= rightMin)
                return (m + n) % 2 ? leftMax : 0.5 * (leftMax + rightMin);

            if (leftMax1 > rightMin2) {
                hi = cut1 - 1;
            } else {
                lo = cut1 + 1;
            }
        }
        return -1;
    }

    double approach2(const std::vector<int>& nums1, const std::vector<int>& nums2)
    {
        const int m = nums1.size();
        const int n = nums2.size();
        int i = 0;
        int j = 0;
        auto next = [&]() {
            if (i == m || (j < n && nums2[j] < nums1[i]))
                return nums2[j++];

            return nums1[i++];
        };
        const int mid = (m + n) / 2;
        int curr = 0;
        for (int i = 0; i < mid; ++i) {
            curr = next();
        }
        if ((m + n) % 2)
            return next();

        return 0.5 * (curr + next());
    }

    double approach1(const std::vector<int>& nums1, const std::vector<int>& nums2)
    {
        const int m = nums1.size();
        const int n = nums2.size();
        std::vector<int> merge(m + n);
        for (int i = 0, j = 0, k = 0; k < merge.size(); ++k) {
            if (i == m || (j < n && nums2[j] < nums1[i])) {
                merge[k] = nums2[j++];
            } else {
                merge[k] = nums1[i++];
            }
        }
        if (merge.size() % 2)
            return merge[merge.size() / 2];

        return 0.5 * (merge[merge.size() / 2] + merge[merge.size() / 2 - 1]);
    }
};