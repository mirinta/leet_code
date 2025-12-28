#include <vector>

/**
 * You are given an integer array nums and a non-negative integer k. A sequence of integers seq is
 * called good if there are at most k indices i in the range [0, seq.length - 2] such that seq[i] !=
 * seq[i + 1].
 *
 * Return the maximum possible length of a good subsequence of nums.
 *
 * ! 1 <= nums.length <= 500
 * ! 1 <= nums[i] <= 10^9
 * ! 0 <= k <= min(nums.length, 25)
 */

class Solution {
public:
    int maximumLength(std::vector<int>& nums, int k)
    {
        // dp[i][j] = max length of a valid subsequence of nums[0:i] ending at nums[i]
        // with at most j indices x such that seq[x] != seq[x+1]
        const int n = nums.size();
        std::vector<std::vector<int>> dp(n, std::vector<int>(k + 1, 0));
        for (int i = 0; i < n; ++i) {
            dp[i][0] = 1; // a sequence with only one element is valid iff k = 0
        }
        int result = 0;
        for (int i = 0; i < n; ++i) {
            // i+1 elements have at most i valid indices
            for (int j = 0; j <= std::min(i, k); ++j) {
                for (int x = i - 1; x >= 0; --x) {
                    if (nums[x] == nums[i]) {
                        dp[i][j] = std::max(dp[i][j], 1 + dp[x][j]);
                    } else if (j > 0) {
                        dp[i][j] = std::max(dp[i][j], 1 + dp[x][j - 1]);
                    }
                }
                result = std::max(result, dp[i][j]);
            }
        }
        return result;
    }
};