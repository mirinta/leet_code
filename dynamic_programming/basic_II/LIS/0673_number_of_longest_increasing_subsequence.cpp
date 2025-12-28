#include <array>
#include <vector>

/**
 * Given an integer array "nums", return the number of longest increasing subsequences.
 *
 * Notice that the sequence has to be strictly increasing.
 *
 * ! 1 <= nums.length <= 2000
 * ! -10^6 <= nums[i] <= 10^6
 */

class Solution {
public:
    int findNumberOfLIS(std::vector<int>& nums)
    {
        // dp[i][0] = length of the LIS of nums[0:i] ending at nums[i]
        // dp[i][1] = num of LIS of nums[0:i] ending at nums[i] with length equal to dp[i][0]
        const int n = nums.size();
        std::vector<std::array<int, 2>> dp(n, {1, 1});
        int lengthOfLIS = 1;
        for (int i = 1; i < n; ++i) {
            for (int j = i - 1; j >= 0; --j) {
                if (nums[i] <= nums[j])
                    continue;

                if (1 + dp[j][0] > dp[i][0]) {
                    dp[i][0] = 1 + dp[j][0];
                    dp[i][1] = dp[j][1];
                } else if (1 + dp[j][0] == dp[i][0]) {
                    dp[i][1] += dp[j][1];
                }
            }
            lengthOfLIS = std::max(lengthOfLIS, dp[i][0]);
        }
        int result = 0;
        for (const auto& [length, count] : dp) {
            if (length == lengthOfLIS) {
                result += count;
            }
        }
        return result;
    }
};