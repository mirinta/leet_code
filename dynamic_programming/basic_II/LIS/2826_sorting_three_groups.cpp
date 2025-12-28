#include <array>
#include <vector>

/**
 * You are given an integer array nums. Each element in nums is 1, 2 or 3. In each operation, you
 * can remove an element from nums. Return the minimum number of operations to make nums
 * non-decreasing.
 *
 * ! 1 <= nums.length <= 100
 * ! 1 <= nums[i] <= 3
 *
 * ! Follow-up: Can you come up with an algorithm that runs in O(n) time complexity?
 */

class Solution {
public:
    int minimumOperations(std::vector<int>& nums)
    {
        return approach2(nums);
    }

private:
    int approach2(const std::vector<int>& nums)
    {
        // dp[i][0] = length of the longest non-decreasing subsequence of nums[0:i] while the last
        // element is 1
        // dp[i][1] = length of the longest non-decreasing subsequence of nums[0:i] while the last
        // element is 2
        // dp[i][2] = length of the longest non-decreasing subsequence of nums[0:i] while the last
        // element is 3
        const int n = nums.size();
        std::vector<std::array<int, 3>> dp(n, {0, 0, 0});
        dp[0][nums[0] - 1] = 1;
        for (int i = 1; i < n; ++i) {
            dp[i] = dp[i - 1]; // nums[i] is not picked
            if (nums[i] == 3) {
                dp[i][2] = std::max(dp[i][2], 1 + std::max({dp[i - 1][0], dp[i - 1][1], dp[i - 1][2]}));
            } else if (nums[i] == 2) {
                dp[i][1] = std::max(dp[i][1], 1 + std::max(dp[i - 1][0], dp[i - 1][1]));
            } else {
                dp[i][0] = std::max(dp[i][0], 1 + dp[i - 1][0]);
            }
        }
        return n - std::max({dp[n - 1][0], dp[n - 1][1], dp[n - 1][2]});
    }

    int approach1(const std::vector<int>& nums)
    {
        // dp[i] = length of the longest non-decreasing subsequence of nums[0:i] ending at nums[i]
        const int n = nums.size();
        std::vector<int> dp(n, 1);
        int lengthOfLIS = 1;
        for (int i = 1; i < n; ++i) {
            for (int j = i - 1; j >= 0; --j) {
                if (nums[i] >= nums[j]) {
                    dp[i] = std::max(dp[i], 1 + dp[j]);
                }
            }
            lengthOfLIS = std::max(lengthOfLIS, dp[i]);
        }
        return n - lengthOfLIS;
    }
};