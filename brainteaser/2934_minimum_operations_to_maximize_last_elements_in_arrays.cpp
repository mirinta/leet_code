#include <vector>

/**
 * You are given two 0-indexed integer arrays, nums1 and nums2, both having length n.
 *
 * You are allowed to perform a series of operations (possibly none).
 *
 * In an operation, you select an index i in the range [0, n - 1] and swap the values of nums1[i]
 * and nums2[i].
 *
 * Your task is to find the minimum number of operations required to satisfy the following
conditions:
 *
 * - nums1[n - 1] is equal to the maximum value among all elements of nums1, i.e., nums1[n - 1] =
max(nums1[0], nums1[1], ..., nums1[n - 1]).
 *
 * - nums2[n - 1] is equal to the maximum value among all elements of nums2, i.e., nums2[n - 1] =
 * max(nums2[0], nums2[1], ..., nums2[n - 1]).
 *
 * Return an integer denoting the minimum number of operations needed to meet both conditions, or -1
 * if it is impossible to satisfy both conditions.
 *
 * ! 1 <= n == nums1.length == nums2.length <= 1000
 * ! 1 <= nums1[i] <= 10^9
 * ! 1 <= nums2[i] <= 10^9
 */

class Solution {
public:
    int minOperations(std::vector<int>& nums1, std::vector<int>& nums2)
    {
        const int case1 = helper(nums1, nums2, nums1.back(), nums2.back());
        int case2 = helper(nums1, nums2, nums2.back(), nums1.back());
        if (case2 != -1) {
            case2++;
        }
        if (case1 != -1 && case2 != -1)
            return std::min(case1, case2);

        return case1 == -1 ? case2 : case1;
    }

private:
    int helper(const std::vector<int>& nums1, const std::vector<int>& nums2, int max1, int max2)
    {
        int count = 0;
        for (int i = 0; i < nums1.size() - 1; ++i) {
            if (nums1[i] <= max1 && nums2[i] <= max2)
                continue;

            if (nums1[i] > max1 && nums1[i] <= max2 && nums2[i] <= max1) {
                count++;
            } else if (nums2[i] > max2 && nums2[i] <= max1 && nums1[i] <= max2) {
                count++;
            } else {
                return -1;
            }
        }
        return count;
    }
};