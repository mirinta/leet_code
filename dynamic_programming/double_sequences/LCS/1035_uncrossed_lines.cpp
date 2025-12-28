#include <vector>

/**
 * You are given two integer arrays nums1 and nums2. We write the integers of nums1 and nums2 (in
 * the order they are given) on two separate horizontal lines.
 *
 * We may draw connecting lines: a straight line connecting two numbers nums1[i] and nums2[j] such
 * that:
 *
 * - nums1[i] == nums2[j], and
 *
 * - the line we draw does not intersect any other connecting (non-horizontal) line.
 *
 * Note that a connecting line cannot intersect even at the endpoints (i.e., each number can only
 * belong to one connecting line).
 *
 * Return the maximum number of connecting lines we can draw in this way.
 *
 * ! 1 <= nums1.length, nums2.length <= 500
 * ! 1 <= nums1[i], nums2[j] <= 2000
 */

class Solution {
public:
    int maxUncrossedLines(std::vector<int>& nums1, std::vector<int>& nums2)
    {
        return approach2(nums1, nums2);
    }

private:
    int approach2(const std::vector<int>& nums1, const std::vector<int>& nums2)
    {
        const int n = nums2.size();
        std::vector<int> dp(n + 1, 0);
        for (const auto& v1 : nums1) {
            auto prev = dp;
            for (int j = 1; j <= n; ++j) {
                if (v1 == nums2[j - 1]) {
                    dp[j] = 1 + prev[j - 1];
                } else {
                    dp[j] = std::max(prev[j], dp[j - 1]);
                }
            }
        }
        return dp[n];
    }

    int approach1(const std::vector<int>& nums1, const std::vector<int>& nums2)
    {
        // dp[i][j] = length of the LCS of nums1[0:i-1] and nums2[0:j-1]
        const int m = nums1.size();
        const int n = nums2.size();
        std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1, 0));
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (nums1[i - 1] == nums2[j - 1]) {
                    dp[i][j] = 1 + dp[i - 1][j - 1];
                } else {
                    dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }
        return dp[m][n];
    }
};