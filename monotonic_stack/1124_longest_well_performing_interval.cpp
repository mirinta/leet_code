#include <stack>
#include <vector>

/**
 * We are given hours, a list of the number of hours worked per day for a given employee.
 *
 * A day is considered to be a tiring day if and only if the number of hours worked is (strictly)
 * greater than 8.
 *
 * A well-performing interval is an interval of days for which the number of tiring days is strictly
 * larger than the number of non-tiring days.
 *
 * Return the length of the longest well-performing interval.
 *
 * ! 1 <= hours.length <= 10^4
 * ! 0 <= hours[i] <= 16
 */

class Solution {
public:
    int longestWPI(std::vector<int>& hours)
    {
        // +1 flag for nums[i] > 8
        // -1 flag for nums[i] <= 8
        // let presum[i] = num of flags of hours[0:i]
        // if hours[j+1:i] is a valid subarray,
        // then presum[i] > presum[j]
        // i.e, given i, we need to find the furthest j
        // such that j < i and presum[j] < presum[i]
        // it is similar to LC.962
        const int n = hours.size();
        std::vector<int> presum(n + 1, 0);
        for (int i = 1; i <= n; ++i) {
            presum[i] = presum[i - 1] + (hours[i - 1] > 8 ? 1 : -1);
        }
        std::stack<int> stack; // strictly decreasing
        for (int i = 0; i < presum.size(); ++i) {
            if (stack.empty() || presum[i] < presum[stack.top()]) {
                stack.push(i);
            }
        }
        int result = 0;
        for (int i = presum.size() - 1; i >= 0; --i) {
            while (!stack.empty() && presum[i] > presum[stack.top()]) {
                result = std::max(result, i - stack.top());
                stack.pop();
            }
        }
        return result;
    }
};