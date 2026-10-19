#include <stack>
#include <string>

/**
 * Given a balanced parentheses string s, return the score of the string.
 *
 * The score of a balanced parentheses string is based on the following rule:
 *
 * - "()" has score 1.
 *
 * - AB has score A + B, where A and B are balanced parentheses strings.
 *
 * - (A) has score 2 * A, where A is a balanced parentheses string.
 *
 * ! 2 <= s.length <= 50
 * ! s consists of only '(' and ')'.
 * ! s is a balanced parentheses string.
 */

class Solution {
public:
    int scoreOfParentheses(std::string& s)
    {
        const int n = s.size();
        std::stack<std::pair<int, int>> stack; // <depth, score>
        for (int i = 0, depth = 0; i < n; ++i) {
            depth += s[i] == '(' ? 1 : -1;
            if (s[i] == '(')
                continue;

            if (s[i - 1] == '(') {
                stack.emplace(depth, 1);
                continue;
            }
            int sum = 0;
            while (!stack.empty() && stack.top().first > depth) {
                sum += stack.top().second;
                stack.pop();
            }
            stack.emplace(depth, 2 * sum);
        }
        int result = 0;
        while (!stack.empty()) {
            result += stack.top().second;
            stack.pop();
        }
        return result;
    }
};
