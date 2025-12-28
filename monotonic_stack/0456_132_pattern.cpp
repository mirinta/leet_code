#include <stack>
#include <vector>

/**
 * Given an array of n integers nums, a 132 pattern is a subsequence of three integers nums[i],
 * nums[j] and nums[k] such that i < j < k and nums[i] < nums[k] < nums[j].
 *
 * Return true if there is a 132 pattern in nums, otherwise, return false.
 *
 * ! n == nums.length
 * ! 1 <= n <= 2 * 10^5
 * ! -10^9 <= nums[i] <= 10^9
 */

class Solution {
public:
    bool find132pattern(std::vector<int>& nums)
    {
        if (nums.size() < 3)
            return false;

        const int n = nums.size();
        std::vector<int> leftMin(n); // leftMin[i] = min of nums[0:i-1]
        leftMin[0] = INT_MAX;
        for (int i = 1; i < n; ++i) {
            leftMin[i] = std::min(leftMin[i - 1], nums[i - 1]);
        }
        std::stack<int> stack;
        for (int j = n - 1; j >= 0; --j) {
            while (!stack.empty() && leftMin[j] >= nums[stack.top()]) {
                stack.pop();
            }
            if (!stack.empty() && nums[j] > nums[stack.top()])
                return true;

            stack.push(j);
        }
        return false;
    }
};