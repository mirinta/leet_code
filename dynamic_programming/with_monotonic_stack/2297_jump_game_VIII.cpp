#include <limits>
#include <stack>
#include <vector>

/**
 * You are given a 0-indexed integer array nums of length n. You are initially standing at index 0.
 * You can jump from index i to index j where i < j if:
 *
 * - nums[i] <= nums[j] and nums[k] < nums[i] for all indexes k in the range i < k < j, or
 *
 * - nums[i] > nums[j] and nums[k] >= nums[i] for all indexes k in the range i < k < j.
 *
 * You are also given an integer array costs of length n where costs[i] denotes the cost of jumping
 * to index i.
 *
 * Return the minimum cost to jump to the index n - 1.
 *
 * ! n == nums.length == costs.length
 * ! 1 <= n <= 10^5
 * ! 0 <= nums[i], costs[i] <= 10^5
 */

class Solution {
public:
    long long minCost(std::vector<int>& nums, std::vector<int>& costs)
    {
        return approach2(nums, costs);
    }

private:
    // DP + monotonic stack, one-pass, time O(N), space O(N)
    long long approach2(const std::vector<int>& nums, const std::vector<int>& costs)
    {
        const int n = nums.size();
        std::stack<int> min; // pop if top > nums[i]
        std::stack<int> max; // pop if top <= nums[i]
        std::vector<long long> dp(n, LLONG_MAX);
        dp[0] = 0;
        for (int i = 0; i < n; ++i) {
            while (!min.empty() && nums[min.top()] > nums[i]) {
                dp[i] = std::min(dp[i], dp[min.top()] + costs[i]);
                min.pop();
            }
            min.push(i);
            while (!max.empty() && nums[max.top()] <= nums[i]) {
                dp[i] = std::min(dp[i], dp[max.top()] + costs[i]);
                max.pop();
            }
            max.push(i);
        }
        return dp[n - 1];
    }

    // DP + monotonic stack, three-pass, time O(N), space O(N)
    long long approach1(const std::vector<int>& nums, const std::vector<int>& costs)
    {
        // dp[i] = min cost of jumping to index i
        const int n = nums.size();
        const auto nextGreaterOrEqual = genNextGreaterOrEqual(nums);
        const auto nextSmaller = genNextSmaller(nums);
        std::vector<long long> dp(n, LLONG_MAX);
        dp[0] = 0;
        for (int i = 0; i < n; ++i) {
            if (const int j = nextGreaterOrEqual[i]; j != -1) {
                dp[j] = std::min(dp[j], dp[i] + costs[j]);
            }
            if (const int j = nextSmaller[i]; j != -1) {
                dp[j] = std::min(dp[j], dp[i] + costs[j]);
            }
        }
        return dp[n - 1];
    }

    std::vector<int> genNextSmaller(const std::vector<int>& nums)
    {
        const int n = nums.size();
        std::vector<int> result(n, -1);
        std::stack<int> stack;
        for (int i = n - 1; i >= 0; --i) {
            while (!stack.empty() && nums[stack.top()] >= nums[i]) {
                stack.pop();
            }
            result[i] = stack.empty() ? -1 : stack.top();
            stack.push(i);
        }
        return result;
    }

    std::vector<int> genNextGreaterOrEqual(const std::vector<int>& nums)
    {
        const int n = nums.size();
        std::vector<int> result(n, -1);
        std::stack<int> stack;
        for (int i = n - 1; i >= 0; --i) {
            while (!stack.empty() && nums[stack.top()] < nums[i]) {
                stack.pop();
            }
            result[i] = stack.empty() ? -1 : stack.top();
            stack.push(i);
        }
        return result;
    }
};