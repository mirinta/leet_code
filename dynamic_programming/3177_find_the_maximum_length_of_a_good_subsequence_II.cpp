#include <unordered_map>
#include <vector>

/**
 * You are given an integer array nums and a non-negative integer k. A sequence of integers seq is
 * called good if there are at most k indices i in the range [0, seq.length - 2] such that seq[i] !=
 * seq[i + 1].
 *
 * Return the maximum possible length of a good subsequence of nums.
 *
 * ! 1 <= nums.length <= 5 * 10^3
 * ! 1 <= nums[i] <= 10^9
 * ! 0 <= k <= min(50, nums.length)
 */

class Solution {
public:
    int maximumLength(std::vector<int>& nums, int k)
    {
        const int n = nums.size();
        std::vector<std::vector<int>> dp(n, std::vector<int>(k + 1, 0));
        for (int i = 0; i < n; ++i) {
            dp[i][0] = 1;
        }
        std::vector<int> max(k + 1, 0);
        std::unordered_map<int, int> map;
        int result = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j <= std::min(i, k); ++j) {
                if (map.count(nums[i])) {
                    dp[i][j] = std::max(dp[i][j], 1 + dp[map[nums[i]]][j]);
                }
                if (j > 0) {
                    dp[i][j] = std::max(dp[i][j], 1 + max[j - 1]);
                }
                result = std::max(result, dp[i][j]);
            }
            for (int j = 0; j <= std::min(i, k); ++j) {
                max[j] = std::max(max[j], dp[i][j]);
            }
            map[nums[i]] = i;
        }
        return result;
    }
};