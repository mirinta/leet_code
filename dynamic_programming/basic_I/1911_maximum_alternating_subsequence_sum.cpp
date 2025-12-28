#include <array>
#include <vector>

/**
 * The alternating sum of a 0-indexed array is defined as the sum of the elements at even indices
 * minus the sum of the elements at odd indices.
 *
 * - For example, the alternating sum of [4,2,5,3] is (4 + 5) - (2 + 3) = 4.
 *
 * Given an array nums, return the maximum alternating sum of any subsequence of nums (after
 * re-indexing the elements of the subsequence).
 *
 * A subsequence of an array is a new array generated from the original array by deleting some
 * elements (possibly none) without changing the remaining elements' relative order. For example,
 * [2,7,4] is a subsequence of [4,2,3,7,2,1,4] (the underlined elements), while [2,4,2] is not.
 *
 * ! 1 <= nums.length <= 10^5
 * ! 1 <= nums[i] <= 10^5
 */

class Solution {
public:
    long long maxAlternatingSum(std::vector<int>& nums)
    {
        // it is similar to the "buy and sell stock" problem
        return approach2(nums);
    }

private:
    // DP with space optimization
    long long approach2(const std::vector<int>& nums)
    {
        const int n = nums.size();
        long long sumOfEvenLength = 0;
        long long sumOfOddLength = INT_MIN;
        for (int i = 1; i <= n; ++i) {
            const auto backup = sumOfEvenLength;
            sumOfEvenLength = std::max(sumOfEvenLength, sumOfOddLength - nums[i - 1]);
            sumOfOddLength = std::max(sumOfOddLength, backup + nums[i - 1]);
        }
        return std::max(sumOfEvenLength, sumOfOddLength);
    }

    // DP
    long long approach1(const std::vector<int>& nums)
    {
        // dp[i][0] = max alternating sum of nums[0:i) with even length
        // dp[i][1] = max alternating sum of nums[0:i) with odd length
        // base cases:
        // - dp[0][0] = 0, length = 0 and 0 is an even number
        // - dp[0][1] = INT_MIN
        const int n = nums.size();
        std::vector<std::array<long long, 2>> dp(n + 1, {0, 0});
        dp[0][0] = 0;
        dp[0][1] = INT_MIN;
        for (int i = 1; i <= n; ++i) {
            // index of the last element of an even length array is odd
            dp[i][0] = std::max(dp[i - 1][0], dp[i - 1][1] - nums[i - 1]);
            // index of the last element of an odd length array is even
            dp[i][1] = std::max(dp[i - 1][1], dp[i - 1][0] + nums[i - 1]);
        }
        return std::max(dp[n][0], dp[n][1]);
    }
};
