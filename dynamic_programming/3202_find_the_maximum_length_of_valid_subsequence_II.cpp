#include <vector>

/**
 * You are given an integer array nums and a positive integer k.
 *
 * A subsequence sub of nums with length x is called valid if it satisfies:
 *
 * - (sub[0] + sub[1]) % k == (sub[1] + sub[2]) % k == ... == (sub[x - 2] + sub[x - 1]) % k.
 *
 * Return the length of the longest valid subsequence of nums.
 *
 * ! 2 <= nums.length <= 10^3
 * ! 1 <= nums[i] <= 10^7
 * ! 1 <= k <= 10^3
 */

class Solution {
public:
    int maximumLength(std::vector<int>& nums, int k)
    {
        return approach2(nums, k);
    }

private:
    int approach2(const std::vector<int>& nums, int k)
    {
        // sub[0] % k = sub[2] % k = sub[4] % k = ...
        // sub[1] % k = sub[3] % k = sub[5] % k = ...
        //
        // dp[i][j] = length of the longest valid subsequence that the last two elements satisfies
        // sub.last % k = i and sub.secondLast % k = j
        //
        // sub.last % k = sub.thirdLast % k
        const int n = nums.size();
        std::vector<std::vector<int>> dp(k, std::vector<int>(k, 0));
        int result = 0;
        for (int i = 0; i < n; ++i) {
            const int last = nums[i] % k;
            for (int secondLast = 0; secondLast < k; ++secondLast) {
                dp[last][secondLast] = std::max(dp[last][secondLast], 1 + dp[secondLast][last]);
                result = std::max(result, dp[last][secondLast]);
            }
        }
        return result;
    }

    int approach1(const std::vector<int>& nums, int k)
    {
        // dp[i][j] = length of the longest valid subsequence of nums[0:i] ending at nums[i]
        // and the last two elements satisfies (sub.last + sub.secondLast) % k = j
        const int n = nums.size();
        std::vector<int> last(k, -1); // last[r] = j, the largest j such that nums[j] % k = r
        std::vector<std::vector<int>> dp(n, std::vector<int>(k, 0));
        int result = 0;
        for (int i = 0; i < n; ++i) {
            const int remainder = nums[i] % k;
            for (int j = 0; j < k; ++j) {
                const int target = (j - remainder + k) % k; // +k to prevent negative value
                if (last[target] != -1) {
                    dp[i][j] = 1 + dp[last[target]][j];
                } else {
                    dp[i][j] = 1; // corner case
                }
                result = std::max(result, dp[i][j]);
            }
            last[remainder] = i;
        }
        return result;
    }
};
