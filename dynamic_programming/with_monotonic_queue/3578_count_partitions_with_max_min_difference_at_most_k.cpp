#include <queue>
#include <vector>

/**
 * You are given an integer array nums and an integer k. Your task is to partition nums into one or
 * more non-empty contiguous segments such that in each segment, the difference between its maximum
 * and minimum elements is at most k.
 *
 * Return the total number of ways to partition nums under this condition.
 *
 * Since the answer may be too large, return it modulo 10^9 + 7.
 *
 * ! 2 <= nums.length <= 5 * 10^4
 * ! 1 <= nums[i] <= 10^9
 * ! 0 <= k <= 10^9
 */

class Solution {
public:
    int countPartitions(std::vector<int>& nums, int k)
    {
        static constexpr int kMod = 1e9 + 7;
        // dp[i] = num of valid subarrays of nums[0:i] that
        // the last subarray is ending at nums[i]
        // - if nums[i:i] is valid, dp[i] += dp[i-1]
        // - if nums[i-1:i] is valid, dp[i] += dp[i-2]
        // - ...
        // - if nums[j:i] is valid, dp[i] += dp[j-1]
        // given index i, we need to find the smallest index j such that
        // nums[j:i], nums[j+1:i], ..., nums[i:i] are valid subarrays
        // given index i+1, if j' must be greater than or equal to j
        const int n = nums.size();
        std::vector<int> dp(n, 0);
        std::vector<int> presum(n + 1, 0); // presum[i] = sum of dp[0:i-1]
        std::deque<int> minQ;
        std::deque<int> maxQ;
        for (int i = 0, j = 0; i < n; ++i) {
            while (!minQ.empty() && nums[i] <= nums[minQ.back()]) {
                minQ.pop_back();
            }
            minQ.push_back(i);
            while (!maxQ.empty() && nums[i] >= nums[maxQ.back()]) {
                maxQ.pop_back();
            }
            maxQ.push_back(i);
            while (!minQ.empty() && !maxQ.empty() && nums[maxQ.front()] - nums[minQ.front()] > k) {
                if (minQ.front() == j) {
                    minQ.pop_front();
                }
                if (maxQ.front() == j) {
                    maxQ.pop_front();
                }
                j++;
            }
            dp[i] = (presum[i] - (j == 0 ? -1 : presum[j - 1]) + kMod) % kMod;
            presum[i + 1] = (presum[i] + dp[i]) % kMod;
        }
        return dp[n - 1];
    }
};