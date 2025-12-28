#include <array>
#include <vector>

/**
 * Given a binary array "nums", return the maximum number of consecutive 1's in the array if you can
 * flip at most one 0.
 *
 * ! 1 <= nums.length <= 10^5
 * ! nums[i] is either 0 or 1.
 */

class Solution {
public:
    int findMaxConsecutiveOnes(std::vector<int>& nums)
    {
        return approach3(nums);
    }

private:
    // sliding window, time O(N), space O(1)
    int approach3(const std::vector<int>& nums)
    {
        const int n = nums.size();
        int countZero = 0;
        int result = 0;
        for (int left = 0, right = 0; right < n; ++right) {
            if (nums[right] == 0) {
                countZero++;
            }
            while (countZero > 1) {
                if (nums[left] == 0) {
                    countZero--;
                }
                left++;
            }
            result = std::max(result, right - left + 1);
        }
        return result;
    }

    // DP with space optimization, time O(N), space O(1)
    int approach2(const std::vector<int>& nums)
    {
        const int n = nums.size();
        int flipped = INT_MIN;
        int notFlipped = 0;
        int result = 0;
        for (int i = 1; i <= n; ++i) {
            if (nums[i - 1] == 1) {
                flipped += 1;
                notFlipped += 1;
            } else {
                flipped = notFlipped + 1;
                notFlipped = 0;
            }
            result = std::max({result, flipped, notFlipped});
        }
        return result;
    }

    // DP, time O(N), space O(N)
    int approach1(const std::vector<int>& nums)
    {
        const int n = nums.size();
        // dp[i][1] = max num of consecutive 1's ending at the ith element (1-indexed) with 1 flip
        // dp[i][0] = max num of consecutive 1's ending at the ith element (1-indexed) with 0 flip
        std::vector<std::array<int, 2>> dp(n + 1, {0, 0});
        dp[0][0] = 0;
        dp[0][1] = INT_MIN; // no element, no way to flip
        int result = 0;
        for (int i = 1; i <= n; ++i) {
            if (nums[i - 1] == 1) {
                dp[i][1] = dp[i - 1][1] + 1;
                dp[i][0] = dp[i - 1][0] + 1;
            } else {
                dp[i][1] = dp[i - 1][0] + 1;
                dp[i][0] = 0;
            }
            result = std::max({result, dp[i][0], dp[i][1]});
        }
        return result;
    }
};
