#include <deque>
#include <vector>

/**
 * Given an integer array nums and an integer k, return the length of the shortest non-empty
 * subarray of nums with a sum of at least k. If there is no such subarray, return -1.
 *
 * A subarray is a contiguous part of an array.
 *
 * ! 1 <= nums.length <= 10^5
 * ! -10^5 <= nums[i] <= 10^5
 * ! 1 <= k <= 10^9
 */

class Solution {
public:
    int shortestSubarray(std::vector<int>& nums, int k)
    {
        const int n = nums.size();
        std::vector<long long> prefixSum(1 + n, 0); // prefixSum[i] = sum of nums[0:i-1]
        for (int i = 1; i <= n; ++i) {
            prefixSum[i] = prefixSum[i - 1] + nums[i - 1];
        }
        std::deque<int> deque;
        int result = INT_MAX;
        for (int i = 0; i <= n; ++i) {
            while (!deque.empty() && prefixSum[deque.back()] >= prefixSum[i]) {
                deque.pop_back();
            }
            while (!deque.empty() && prefixSum[i] - prefixSum[deque.front()] >= k) {
                result = std::min(result, i - deque.front());
                deque.pop_front();
            }
            deque.push_back(i);
        }
        return result == INT_MAX ? -1 : result;
    }
};