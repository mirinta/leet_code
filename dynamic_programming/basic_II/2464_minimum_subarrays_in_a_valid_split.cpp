#include <numeric>
#include <vector>

/**
 * You are given an integer array nums.
 *
 * Splitting of an integer array nums into subarrays is valid if:
 *
 * - the greatest common divisor of the first and last elements of each subarray is greater than 1,
 * and
 *
 * - each element of nums belongs to exactly one subarray.
 *
 * Return the minimum number of subarrays in a valid subarray splitting of nums. If a valid subarray
 * splitting is not possible, return -1.
 *
 * Note that:
 *
 * - The greatest common divisor of two numbers is the largest positive integer that evenly divides
 * both numbers.
 *
 * - A subarray is a contiguous non-empty part of an array.
 *
 * ! 1 <= nums.length <= 1000
 * ! 1 <= nums[i] <= 10^5
 */

class Solution {
public:
    int validSubarraySplit(std::vector<int>& nums)
    {
        // dp[i] = min num of subarrays of splitting nums[0:i]
        // X X X X X j-1 j X X i
        // |<-dp[j-1]->|
        const int n = nums.size();
        std::vector<int> dp(n, INT_MAX / 2);
        for (int i = 0; i < n; ++i) {
            for (int j = i; j >= 0; --j) {
                if (std::gcd(nums[i], nums[j]) > 1) {
                    dp[i] = std::min(dp[i], j == 0 ? 1 : dp[j - 1] + 1);
                }
            }
        }
        return dp[n - 1] == INT_MAX / 2 ? -1 : dp[n - 1];
    }
};