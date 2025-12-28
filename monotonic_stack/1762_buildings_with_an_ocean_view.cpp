#include <stack>
#include <vector>

/**
 * There are n buildings in a line. You are given an integer array heights of size n that represents
 * the heights of the buildings in the line.
 *
 * The ocean is to the right of the buildings. A building has an ocean view if the building can see
 * the ocean without obstructions. Formally, a building has an ocean view if all the buildings to
 * its right have a smaller height.
 *
 * Return a list of indices (0-indexed) of buildings that have an ocean view, sorted in increasing
 * order.
 *
 * ! 1 <= heights.length <= 10^5
 * ! 1 <= heights[i] <= 10^9
 */

class Solution {
public:
    std::vector<int> findBuildings(std::vector<int>& heights)
    {
        const int n = heights.size();
        const auto nextGreaterOrEqual = getNextGreaterOrEqual(heights);
        std::vector<int> result;
        for (int i = 0; i < n; ++i) {
            if (nextGreaterOrEqual[i] == n) {
                result.push_back(i);
            }
        }
        return result;
    }

private:
    std::vector<int> getNextGreaterOrEqual(const std::vector<int>& nums)
    {
        const int n = nums.size();
        std::vector<int> result(n);
        std::stack<int> stack;
        for (int i = n - 1; i >= 0; --i) {
            while (!stack.empty() && nums[i] > nums[stack.top()]) {
                stack.pop();
            }
            result[i] = stack.empty() ? n : stack.top();
            stack.push(i);
        }
        return result;
    }
};