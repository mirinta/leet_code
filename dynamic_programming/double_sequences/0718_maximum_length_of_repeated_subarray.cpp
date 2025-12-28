#include <vector>

/**
 * Given two integer arrays nums1 and nums2, return the maximum length of a subarray that appears in
 * both arrays.
 *
 * ! 1 <= nums1.length, nums2.length <= 1000
 * ! 0 <= nums1[i], nums2[i] <= 100
 */

class Solution {
public:
    int findLength(std::vector<int>& nums1, std::vector<int>& nums2)
    {
        // dp[i][j] = length of the longest common subarray of nums1[0:i-1]
        // ending at nums1[i-1] and num2[0:j-1] ending at nums2[j-1]
        const int m = nums1.size();
        const int n = nums2.size();
        std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1, 0));
        int result = 0;
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (nums1[i - 1] == nums2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                }
                result = std::max(result, dp[i][j]);
            }
        }
        return result;
    }
};