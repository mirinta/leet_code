#include <vector>

/**
 * Given an integer array arr, partition the array into (contiguous) subarrays of length at most k.
 * After partitioning, each subarray has their values changed to become the maximum value of that
 * subarray.
 *
 * Return the largest sum of the given array after partitioning. Test cases are generated so that
 * the answer fits in a 32-bit integer.
 *
 * ! 1 <= arr.length <= 500
 * ! 0 <= arr[i] <= 10^9
 * ! 1 <= k <= arr.length
 */

class Solution {
public:
    int maxSumAfterPartitioning(std::vector<int>& arr, int k)
    {
        // dp[i] = largest sum of arr[0:i) after partitioning
        // X X X X X X j X X X i-1 i
        // |<-dp[j]->| |<-group->|
        // |<-------dp[i]------->|
        // group length <= k
        // dp[i] = dp[j] + (i-j) * max of nums[j:i-1]
        const int n = arr.size();
        std::vector<int> dp(n + 1, 0);
        int result = INT_MIN;
        for (int i = 1; i <= n; ++i) {
            int max = INT_MIN;
            for (int j = i - 1; j >= std::max(0, i - k); --j) {
                max = std::max(max, arr[j]);
                dp[i] = std::max(dp[i], dp[j] + max * (i - j));
            }
            result = std::max(result, dp[i]);
        }
        return result;
    }
};