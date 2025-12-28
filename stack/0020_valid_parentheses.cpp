#include <stack>
#include <string>

/**
 * Given a string "s" containing just the characters '(', ')', '{', '}', '[' and ']', determine if
 * the input string is valid.
 *
 * An input string is valid if:
 *
 * - Open brackets must be closed by the same type of brackets.
 *
 * - Open brackets must be closed in the correct order.
 *
 * - Every close brackets has a corresponding open bracket of the same type.
 *
 * ! 1 <= s.length <= 10^4
 * ! s consists of parentheses only '()[]{}'.
 */

class Solution {
public:
    bool isValid(std::string s)
    {
        if (s.size() < 2)
            return false;

        std::stack<char> stack;
        for (const auto& c : s) {
            if (c == '(') {
                stack.push(')');
            } else if (c == '[') {
                stack.push(']');
            } else if (c == '{') {
                stack.push('}');
            } else if (!stack.empty() && c == stack.top()) {
                stack.pop();
            } else {
                return false;
            }
        }
        return stack.empty();
    }
};
