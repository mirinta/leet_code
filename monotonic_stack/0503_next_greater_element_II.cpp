#include <stack>
#include <vector>

/**
 * Given a circular integer array nums (i.e., the next element of nums[nums.length - 1] is nums[0]),
 * return the next greater number for every element in nums.
 *
 * The next greater number of a number x is the first greater number to its traversing-order next in
 * the array, which means you could search circularly to find its next greater number. If it doesn't
 * exist, return -1 for this number.
 *
 * ! 1 <= nums.length <= 10^4
 * ! -10^9 <= nums[i] <= 10^9
 */

class Solution {
public:
    std::vector<int> nextGreaterElements(std::vector<int>& nums)
    {
        const int n = nums.size();
        std::stack<int> stack;
        std::vector<int> result(n);
        for (int i = 2 * n - 1; i >= 0; --i) {
            while (!stack.empty() && nums[i % n] >= stack.top()) {
                stack.pop();
            }
            result[i % n] = stack.empty() ? -1 : stack.top();
            stack.push(nums[i % n]);
        }
        return result;
    }
};