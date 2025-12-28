#include <queue>
#include <vector>

/**
 * You are given a 0-indexed integer array nums and an integer k.
 *
 * You are initially standing at index 0. In one move, you can jump at most k steps forward without
 * going outside the boundaries of the array. That is, you can jump from index i to any index in the
 * range [i + 1, min(n - 1, i + k)] inclusive.
 *
 * You want to reach the last index of the array (index n - 1). Your score is the sum of all nums[j]
 * for each index j you visited in the array.
 *
 * Return the maximum score you can get.
 *
 * ! 1 <= nums.length, k <= 10^5
 * ! -10^4 <= nums[i] <= 10^4
 */

class Solution {
public:
    int maxResult(std::vector<int>& nums, int k)
    {
        // dp[i] = max score of jumping from index 0 to index i
        //   dp[i] = max(dp[i-1],dp[i-2],...,dp[i-k])+nums[i]
        // dp[i+1] = max(dp[i],dp[i-1],...,dp[i-k],dp[i-k+1])+nums[i+1]
        // it is similar to the problem of "sliding window maximum"
        // we need to maintain a monotonic decreasing queue
        const int n = nums.size();
        std::deque<std::pair<int, int>> deque; // <index, val>
        deque.emplace_back(0, nums[0]);
        for (int i = 1; i < n; ++i) {
            while (!deque.empty() && i - deque.front().first > k) {
                deque.pop_front();
            }
            if (deque.empty())
                break;

            const int dpI = deque.front().second + nums[i];
            while (!deque.empty() && dpI > deque.back().second) {
                deque.pop_back();
            }
            deque.emplace_back(i, dpI);
        } // dp_n-1 is the final answer and it is at the end of the deque
        return deque.empty() ? 0 : deque.back().second;
    }
};