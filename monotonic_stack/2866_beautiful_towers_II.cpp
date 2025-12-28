#include <stack>
#include <vector>

/**
 * You are given a 0-indexed array maxHeights of n integers.
 *
 * You are tasked with building n towers in the coordinate line. The ith tower is built at
 * coordinate i and has a height of heights[i].
 *
 * A configuration of towers is beautiful if the following conditions hold:
 *
 * 1. 1 <= heights[i] <= maxHeights[i]
 *
 * 2. heights is a mountain array.
 *
 * Array heights is a mountain if there exists an index i such that:
 *
 * 1. For all 0 < j <= i, heights[j - 1] <= heights[j]
 *
 * 2. For all i <= k < n - 1, heights[k + 1] <= heights[k]
 *
 * Return the maximum possible sum of heights of a beautiful configuration of towers.
 *
 * ! 1 <= n == maxHeights <= 10^5
 * ! 1 <= maxHeights[i] <= 10^9
 */

class Solution {
public:
    long long maximumSumOfHeights(std::vector<int>& maxHeights)
    {
        const int n = maxHeights.size();
        const auto leftMax = getLeftMax(maxHeights);
        const auto rightMax = getRightMax(maxHeights);
        long long result = 0;
        for (int i = 0; i < n; ++i) {
            result = std::max(result, leftMax[i] + rightMax[i] - maxHeights[i]);
        }
        return result;
    }

private:
    // leftMax[i] = max sum of heights of nums[0:i] using nums[i] as peak
    std::vector<long long> getLeftMax(const std::vector<int>& nums)
    {
        const int n = nums.size();
        std::stack<int> stack;
        long long sum = 0;
        std::vector<long long> result(n);
        for (int i = 0; i < n; ++i) {
            while (!stack.empty() && nums[i] < nums[stack.top()]) {
                const int p1 = stack.top();
                stack.pop();
                const int p2 = stack.empty() ? -1 : stack.top();
                sum -= static_cast<long long>(p1 - p2) * nums[p1];
            }
            sum += static_cast<long long>(i - (stack.empty() ? -1 : stack.top())) * nums[i];
            result[i] = sum;
            stack.push(i);
        }
        return result;
    }

    // rightMax[i] = max sum of heights of nums[i:n-1] using nums[i] as peak
    std::vector<long long> getRightMax(const std::vector<int>& nums)
    {
        const int n = nums.size();
        std::stack<int> stack;
        long long sum = 0;
        std::vector<long long> result(n);
        for (int i = n - 1; i >= 0; --i) {
            while (!stack.empty() && nums[i] < nums[stack.top()]) {
                const int p1 = stack.top();
                stack.pop();
                const int p2 = stack.empty() ? n : stack.top();
                sum -= static_cast<long long>(p2 - p1) * nums[p1];
            }
            sum += static_cast<long long>((stack.empty() ? n : stack.top()) - i) * nums[i];
            result[i] = sum;
            stack.push(i);
        }
        return result;
    }
};