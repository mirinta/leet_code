#include <unordered_map>
#include <vector>

/**
 * Given an array "nums" of integers, return the length of the longest arithmetic subsequence in
 * "nums".
 *
 * Note that:
 *
 * - A subsequence is an array that can be derived from another array by deleting some or no
 * elements without changing the order of the remaining elements.
 *
 * - A sequence "seq" is arithmetic if seq[i + 1] - seq[i] are all the same value (for 0 <= i <
 * seq.length - 1).
 *
 * ! 2 <= nums.length <= 1000
 * ! 0 <= nums[i] <= 500
 */

class Solution {
public:
    int longestArithSeqLength(const std::vector<int>& nums)
    {
        if (nums.size() < 2)
            return 0;

        const auto n = nums.size();
        // dp[i][diff] = length of LAC that ends with nums[i] with diff as the common difference
        std::vector<std::unordered_map<int, int>> dp(n, std::unordered_map<int, int>{});
        int result = INT_MIN;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < i; ++j) {
                const auto diff = nums[i] - nums[j];
                if (!dp[j].count(diff)) {
                    dp[i][diff] = 2;
                } else {
                    dp[i][diff] = dp[j][diff] + 1;
                }
                result = std::max(result, dp[i][diff]);
            }
        }
        return result;
    }
};