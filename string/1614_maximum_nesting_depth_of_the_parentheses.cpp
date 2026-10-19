#include <stack>
#include <string>

/**
 * Given a valid parentheses string s, return the nesting depth of s. The nesting depth is the maximum number of nested
 * parentheses.
 *
 * ! 1 <= s.length <= 100
 * ! s consists of digits 0-9 and characters '+', '-', '*', '/', '(', and ')'.
 * ! It is guaranteed that parentheses expression s is a VPS.
 */

class Solution {
public:
    int maxDepth(std::string& s)
    {
        std::stack<char> stack;
        int result = 0;
        for (const auto& c : s) {
            if (c == '(') {
                stack.push(c);
            } else if (c == ')') {
                stack.pop();
            }
            result = std::max<int>(result, stack.size());
        }
        return result;
    }
};
