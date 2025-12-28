#include <stack>
#include <vector>

/**
 * 输入两个整数序列，第一个序列表示栈的压入顺序，请判断第二个序列是否为该栈的弹出顺序。
 *
 * 假设压入栈的所有数字均不相等。
 *
 * 例如，序列 {1,2,3,4,5} 是某栈的压栈序列，序列 {4,5,3,2,1} 是该压栈序列对应的一个弹出序列，
 * 但 {4,3,5,1,2} 就不可能是该压栈序列的弹出序列。
 *
 * ! 0 <= pushed.length == popped.length <= 1000
 * ! 0 <= pushed[i], popped[i] < 1000
 * ! pushed 是 popped 的排列。
 */

class Solution {
public:
    bool validateStackSequences(std::vector<int>& pushed, std::vector<int>& popped)
    {
        if (popped.empty())
            return true;

        if (pushed.empty())
            return false;

        std::stack<int> stack;
        int i = 0;
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