#include <vector>

/**
 * You are given two integer arrays of the same length nums1 and nums2. In one operation, you are
 * allowed to swap nums1[i] with nums2[i].
 *
 * - For example, if nums1 = [1,2,3,8], and nums2 = [5,6,7,4], you can swap the element at i = 3 to
 * obtain nums1 = [1,2,3,4] and nums2 = [5,6,7,8].
 *
 * Return the minimum number of needed operations to make nums1 and nums2 strictly increasing. The
 * test cases are generated so that the given input always makes it possible.
 *
 * An array arr is strictly increasing if and only if
 * arr[0] < arr[1] < arr[2] < ... < arr[arr.length - 1].
 *
 * ! 2 <= nums1.length <= 10^5
 * ! nums2.length == nums1.length
 * ! 0 <= nums1[i], nums2[i] <= 2 * 10^5
 */

class Solution {
public:
    int minSwap(std::vector<int>& nums1, std::vector<int>& nums2)
    {
        // space optimization of approach1:
        const auto n = nums1.size();
        int swapped = 1;
        int notSwapped = 0;
        for (int i = 2; i <= n; ++i) {
            int prevSwapped = swapped;
            int prevNotSwapped = notSwapped;
            swapped = INT_MAX;
            notSwapped = INT_MAX;
            // case 1: this round doesn't need to swap while previous element is not swapped
            if (nums1[i - 1] > nums1[i - 2] && nums2[i - 1] > nums2[i - 2]) {
                notSwapped = std::min(notSwapped, prevNotSwapped);
            }
            // case 2: this round doesn't need to swap while previous element is swapped
            if (nums1[i - 1] > nums2[i - 2] && nums2[i - 1] > nums1[i - 2]) {
                notSwapped = std::min(notSwapped, prevSwapped);
            }
            // case 3: this round need to swap while previous element is not swapped
            if (nums2[i - 1] > nums1[i - 2] && nums1[i - 1] > nums2[i - 2]) {
                swapped = std::min(swapped, prevNotSwapped + 1);
            }
            // case 4: this round need to swap while previous element is swapped
            if (nums2[i - 1] > nums2[i - 2] && nums1[i - 1] > nums1[i - 2]) {
                swapped = std::min(swapped, prevSwapped + 1);
            }
        }
        return std::min(swapped, notSwapped);
    }

private:
    int approach1(std::vector<int>& nums1, std::vector<int>& nums2)
    {
        const auto n = nums1.size();
        // dp[i][0] = min operations to make nums1[0:i) and nums2[0:i) strictly increasing without
        // swapping the ith element dp[i][1] = min operations to make nums1[0:i) and nums2[0:i)
        // strictly increasing with swapping the ith element
        std::vector<std::vector<int>> dp(n + 1, std::vector<int>(2, INT_MAX));
        // base case: both nums1 and nums2 have one element, they are all strictly increasing
        // - dp[1][0] = 0
        // - dp[1][1] = 1
        dp[1][0] = 0;
        dp[1][1] = 1;
        for (int i = 2; i <= n; ++i) {
            // case 1: this round doesn't need to swap while previous element is not swapped
            if (nums1[i - 1] > nums1[i - 2] && nums2[i - 1] > nums2[i - 2]) {
                dp[i][0] = std::min(dp[i][0], dp[i - 1][0]);
            }
            // case 2: this round doesn't need to swap while previous element is swapped
            if (nums1[i - 1] > nums2[i - 2] && nums2[i - 1] > nums1[i - 2]) {
                dp[i][0] = std::min(dp[i][0], dp[i - 1][1]);
            }
            // case 3: this round need to swap while previous element is not swapped
            if (nums2[i - 1] > nums1[i - 2] && nums1[i - 1] > nums2[i - 2]) {
                dp[i][1] = std::min(dp[i][1], dp[i - 1][0] + 1);
            }
            // case 4: this round need to swap while previous element is swapped
            if (nums2[i - 1] > nums2[i - 2] && nums1[i - 1] > nums1[i - 2]) {
                dp[i][1] = std::min(dp[i][1], dp[i - 1][1] + 1);
            }
        }
        return std::min(dp[n][0], dp[n][1]);
    }
};