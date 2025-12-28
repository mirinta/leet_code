#include <unordered_map>
#include <vector>

/**
 * Given an integer array nums, return the number of all the arithmetic subsequences of nums.
 *
 * A sequence of numbers is called arithmetic if it consists of at least three elements and if the
 * difference between any two consecutive elements is the same.
 *
 * - For example, [1, 3, 5, 7, 9], [7, 7, 7, 7], and [3, -1, -5, -9] are arithmetic sequences.
 *
 * - For example, [1, 1, 2, 5, 7] is not an arithmetic sequence.
 *
 * A subsequence of an array is a sequence that can be formed by removing some elements (possibly
 * none) of the array.
 *
 * - For example, [2,5,10] is a subsequence of [1,2,1,2,4,1,5,10].
 *
 * The test cases are generated so that the answer fits in 32-bit integer.
 *
 * ! 1  <= nums.length <= 1000
 * ! -2^31 <= nums[i] <= 2^31 - 1
 */

class Solution {
public:
    int numberOfArithmeticSlices(std::vector<int>& nums)
    {
        const int n = nums.size();
        // dp[i][j] = num of arithmetic subsequences ending at nums[i] with j as the common
        // difference
        // here, we define an arithmetic subsequence must have at least two elements
        std::vector<std::unordered_map<long long, int>> dp(n);
        int result = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < i; ++j) {
                const long long diff = static_cast<long long>(nums[i]) - nums[j];
                // we can append nums[i] to all subsequences of dp[j][diff]
                // and there's an extra valid subsequence: [nums[j], nums[i]]
                dp[i][diff] += dp[j][diff] + 1;
                result += dp[j][diff]; // the extra subsequence only has two elements
            }
        }
        return result;
    }
};