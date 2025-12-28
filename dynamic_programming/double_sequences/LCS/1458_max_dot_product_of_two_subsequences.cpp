#include <vector>

/**
 * Given two arrays nums1 and nums2.
 *
 * Return the maximum dot product between non-empty subsequences of nums1 and nums2 with the same
 * length.
 *
 * A subsequence of a array is a new array which is formed from the original array by deleting some
 * (can be none) of the characters without disturbing the relative positions of the remaining
 * characters. (ie, [2,3,5] is a subsequence of [1,2,3,4,5] while [1,5,3] is not).
 *
 * ! 1 <= nums1.length, nums2.length <= 500
 * ! -1000 <= nums1[i], nums2[i] <= 1000
 */

class Solution {
public:
    int maxDotProduct(std::vector<int>& nums1, std::vector<int>& nums2)
    {
        return approach2(nums1, nums2);
    }

private:
    int approach2(const std::vector<int>& nums1, const std::vector<int>& nums2)
    {
        const int n = nums2.size();
        std::vector<long long> dp(n + 1, INT_MIN);
        for (const long long x1 : nums1) {
            auto prev = dp;
            for (int j = 1; j <= n; ++j) {
                const long long x2 = nums2[j - 1];
                const long long case1 = std::max(x1 * x2, prev[j - 1] + x1 * x2);
                const long long case2 = std::max(prev[j], dp[j - 1]);
                dp[j] = std::max(case1, case2);
            }
        }
        return dp[n];
    }

    int approach1(const std::vector<int>& nums1, const std::vector<int>& nums2)
    {
        // dp[i][j] = max dot product between non-empty subsequences of nums1[0:i-1]
        // and nums2[j-1]
        const int m = nums1.size();
        const int n = nums2.size();
        std::vector<std::vector<long long>> dp(m + 1, std::vector<long long>(n + 1, INT_MIN));
        for (int i = 1; i <= m; ++i) {
            const long long x1 = nums1[i - 1];
            for (int j = 1; j <= n; ++j) {
                const long long x2 = nums2[j - 1];
                const long long case1 = std::max(x1 * x2, dp[i - 1][j - 1] + x1 * x2);
                const long long case2 = std::max(dp[i - 1][j], dp[i][j - 1]);
                dp[i][j] = std::max(case1, case2);
            }
        }
        return dp[m][n];
    }
};
