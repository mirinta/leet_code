#include <queue>
#include <vector>

/**
 * Given an integer array nums and an integer k, return the maximum sum of a non-empty subsequence
 * of that array such that for every two consecutive integers in the subsequence, nums[i] and
 * nums[j], where i < j, the condition j - i <= k is satisfied.
 *
 * A subsequence of an array is obtained by deleting some number of elements (can be zero) from the
 * array, leaving the remaining elements in their original order.
 *
 * ! 1 <= k <= nums.length <= 10^5
 * ! -10^4 <= nums[i] <= 10^4
 */

class Solution {
public:
    int constrainedSubsetSum(std::vector<int>& nums, int k)
    {
        return approach2(nums, k);
    }

private:
    // DP + Monotonic Queue, time O(N), space O(N)
    int approach2(const std::vector<int>& nums, int k)
    {
        const int n = nums.size();
        std::deque<std::pair<int, int>> deque; // monotonic decreasing, <dp[j], j>
        std::vector<int> dp(n);
        int result = INT_MIN;
        for (int i = 0; i < n; ++i) {
            while (!deque.empty() && i - deque.front().second > k) {
                deque.pop_front();
            }
            dp[i] = nums[i];
            if (!deque.empty()) {
                dp[i] = std::max(dp[i], nums[i] + deque.front().first);
            }
            while (!deque.empty() && dp[i] >= deque.back().first) {
                deque.pop_back();
            }
            deque.emplace_back(dp[i], i);
            result = std::max(result, dp[i]);
        }
        return result;
    }

    // DP + Priority Queue, time O(NlogN), space O(N)
    int approach1(const std::vector<int>& nums, int k)
    {
        // dp[i] = max sum of a non-empty subsequence ending at nums[i] that satisfies the
        // requirements X X j X X X X i dp[i] = max(dp[j]+nums[i], nums[i]) for j in the range
        // [i-k,i-1]
        const int n = nums.size();
        std::vector<int> dp(n);
        std::priority_queue<std::pair<int, int>> pq; // max heap, <dp[j], j>
        int result = INT_MIN;
        for (int i = 0; i < n; ++i) {
            dp[i] = nums[i];
            while (!pq.empty() && i - pq.top().second > k) {
                pq.pop();
            }
            if (!pq.empty()) {
                dp[i] = std::max(dp[i], nums[i] + pq.top().first);
            }
            pq.emplace(dp[i], i);
            result = std::max(result, dp[i]);
        }
        return result;
    }
};