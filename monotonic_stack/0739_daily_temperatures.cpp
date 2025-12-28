#include <stack>
#include <vector>

/**
 * Given an array of integers temperatures represents the daily temperatures, return an array answer
 * such that answer[i] is the number of days you have to wait after the ith day to get a warmer
 * temperature. If there is no future day for which this is possible, keep answer[i] == 0 instead.
 *
 * ! 1 <= temperatures.length <= 10^5
 * ! 30 <= temperatures[i] <= 100
 */

class Solution {
public:
    std::vector<int> dailyTemperatures(std::vector<int>& temperatures)
    {
        return approach2(temperatures);
    }

private:
    std::vector<int> approach2(const std::vector<int>& nums)
    {
        const int n = nums.size();
        std::stack<int> stack;
        std::vector<int> result(n, 0);
        for (int i = 0; i < n; ++i) {
            while (!stack.empty() && nums[i] > nums[stack.top()]) {
                result[stack.top()] = i - stack.top();
                stack.pop();
            }
            stack.push(i);
        }
        return result;
    }

    std::vector<int> approach1(const std::vector<int>& nums)
    {
        const int n = nums.size();
        std::stack<int> stack;
        std::vector<int> result(n);
        for (int i = n - 1; i >= 0; --i) {
            while (!stack.empty() && nums[stack.top()] <= nums[i]) {
                stack.pop();
            }
            result[i] = stack.empty() ? 0 : stack.top() - i;
            stack.push(i);
        }
        return result;
    }
};
