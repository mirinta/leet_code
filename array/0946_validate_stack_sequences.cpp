#include <stack>
#include <vector>

/**
 * Given two integer arrays pushed and popped each with distinct values, return true if this could
 * have been the result of a sequence of push and pop operations on an initially empty stack, or
 * false otherwise.
 */

class Solution {
public:
    bool validateStackSequences(const std::vector<int>& pushed, const std::vector<int>& popped)
    {
        std::stack<int> stack;
        int i = 0; // for popped array
        for (const auto& val : pushed) {
            stack.push(val);
            while (!stack.empty() && i < popped.size() && popped[i] == stack.top()) {
                i++;
                stack.pop();
            }
        }
        return i == popped.size();
    }
};