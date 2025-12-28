#include <vector>

/**
 * You are given a 0-indexed integer array nums of length n and an integer k. In an operation, you
 * can choose an element and multiply it by 2.
 *
 * Return the maximum possible value of nums[0] | nums[1] | ... | nums[n - 1] that can be obtained
 * after applying the operation on nums at most k times.
 *
 * Note that a | b denotes the bitwise or between two integers a and b.
 *
 * ! 1 <= nums.length <= 10^5
 * ! 1 <= nums[i] <= 10^9
 * ! 1 <= k <= 15
 */

class Solution {
public:
    long long maximumOr(std::vector<int>& nums, int k)
    {
        const int n = nums.size();
        std::vector<long long> prefix(n); // prefix[i] = OR of nums[0:i-1]
        std::vector<long long> suffix(n); // suffix[i] = OR of nums[i+1:n-1]
        for (int i = 1; i < n; ++i) {
            prefix[i] = prefix[i - 1] | nums[i - 1];
            suffix[n - i - 1] = suffix[n - i] | nums[n - i];
        }
        long long result = 0;
        for (int i = 0; i < n; ++i) {
            result = std::max(result, prefix[i] | (static_cast<long long>(nums[i]) << k) | suffix[i]);
        }
        return result;
    }
};