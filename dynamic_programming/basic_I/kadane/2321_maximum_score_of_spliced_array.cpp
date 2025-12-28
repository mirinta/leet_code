#include <array>
#include <vector>

/**
 * You are given two 0-indexed integer arrays nums1 and nums2, both of length n.
 *
 * You can choose two integers left and right where 0 <= left <= right < n and swap the subarray
 * nums1[left...right] with the subarray nums2[left...right].
 *
 * - For example, if nums1 = [1,2,3,4,5] and nums2 = [11,12,13,14,15] and you choose left = 1 and
 * right = 2, nums1 becomes [1,12,13,4,5] and nums2 becomes [11,2,3,14,15].
 *
 * You may choose to apply the mentioned operation once or not do anything.
 *
 * The score of the arrays is the maximum of sum(nums1) and sum(nums2), where sum(arr) is the sum of
 * all the elements in the array arr.
 *
 * Return the maximum possible score.
 *
 * A subarray is a contiguous sequence of elements within an array. arr[left...right] denotes the
 * subarray that contains the elements of nums between indices left and right (inclusive).
 *
 * ! n == nums1.length == nums2.length
 * ! 1 <= n <= 10^5
 * ! 1 <= nums1[i], nums2[i] <= 10^4
 */

class Solution {
public:
    int maximumsSplicedArray(std::vector<int>& nums1, std::vector<int>& nums2)
    {
        // let total1 = sum of nums1[0:n-1], total2 = sum of nums2[0:n-1]
        // replace nums1[left:right] with nums2[left:right]
        // total1' = total1 - sum of nums1[left:right] + sum of nums2[left:right]
        // total2' = total2 - sum of nums2[left:right] + sum of nums1[left:right]
        // let diff[i] = nums2[i] - nums1[i], then
        // total1' = total1 + sum of diff[left:right]
        // total2' = total2 - sum of diff[left:right]
        const int n = nums1.size();
        std::vector<int> diff(n);
        int total1 = 0;
        int total2 = 0;
        for (int i = 0; i < n; ++i) {
            total1 += nums1[i];
            total2 += nums2[i];
            diff[i] = nums2[i] - nums1[i];
        }
        // dp[i][0] = min subarray sum of diff[0:i-1] ending at diff[i-1]
        // dp[i][1] = max subarray sum of diff[0:i-1] ending at diff[i-1]
        std::vector<std::array<int, 2>> dp(n + 1);
        int min = INT_MAX;
        int max = INT_MIN;
        for (int i = 1; i <= n; ++i) {
            dp[i][0] = std::min(diff[i - 1], dp[i - 1][0] + diff[i - 1]);
            dp[i][1] = std::max(diff[i - 1], dp[i - 1][1] + diff[i - 1]);
            min = std::min(min, dp[i][0]);
            max = std::max(max, dp[i][1]);
        }
        const int case1 = std::max(total1 + min, total2 - min);
        const int case2 = std::max(total1 + max, total2 - max);
        return std::max(case1, case2);
    }
};