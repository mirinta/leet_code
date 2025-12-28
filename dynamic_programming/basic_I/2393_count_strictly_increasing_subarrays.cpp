#include <vector>

/**
 * You are given an array nums consisting of positive integers.
 *
 * Return the number of subarrays of nums that are in strictly increasing order.
 *
 * A subarray is a contiguous part of an array.
 *
 * ! 1 <= nums.length <= 10^5
 * ! 1 <= nums[i] <= 10^6
 */

class Solution {
public:
    long long countSubarrays(std::vector<int>& nums)
    {
        return approach3(nums);
    }

private:
    // DP with space optimization, time O(N), space O(1)
    long long approach3(const std::vector<int>& nums)
    {
        long long dp = 1;
        long long result = 1;
        for (int i = 1; i < nums.size(); ++i) {
            if (nums[i] > nums[i - 1]) {
                dp += 1;
            } else {
                dp = 1;
            }
            result += dp;
        }
        return result;
    }

    // DP, time O(N), space O(N)
    long long approach2(const std::vector<int>& nums)
    {
        const int n = nums.size();
        // dp[i] = num of strictly increasing subarray ending at nums[i]
        std::vector<long long> dp(n, 1);
        long long result = 1;
        for (int i = 1; i < n; ++i) {
            if (nums[i] > nums[i - 1]) {
                dp[i] = dp[i - 1] + 1;
            } else {
                dp[i] = 1;
            }
            result += dp[i];
        }
        return result;
    }

    // time O(N), space O(1)
    int approach1(const std::vector<int>& nums)
    {
        // given a strictly increasing array A with length L
        // num of strictly increasing subarrays of A = 1+2+3+...+L
        const int n = nums.size();
        long long result = 0;
        long long length = 1;
        for (int i = 0; i < n; ++i) {
            while (i + 1 < n && nums[i + 1] > nums[i]) {
                length++;
                i++;
            }
            result += (1 + length) * length / 2;
            length = 1;
        }
        return result;
    }
};