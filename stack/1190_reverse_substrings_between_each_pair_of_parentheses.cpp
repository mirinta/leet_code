#include <algorithm>
#include <stack>
#include <string>

/**
 * You are given a string s that consists of lower case English letters and brackets.
 *
 * Reverse the strings in each pair of matching parentheses, starting from the innermost one.
 *
 * Your result should not contain any brackets.
 *
 * ! 1 <= s.length <= 2000
 * ! s only contains lower case English characters and parentheses.
 * ! It is guaranteed that all parentheses are balanced.
 */

class Solution {
public:
    std::string reverseParentheses(std::string s)
    {
        const int n = s.size();
        std::stack<int> stack; // occurrences of '('
        for (int i = 0; i < n; ++i) {
            if (std::isalpha(s[i]))
                continue;

            if (s[i] == '(') {
                stack.push(i);
            } else {
                std::reverse(s.begin() + stack.top() + 1, s.begin() + i);
                stack.pop();
            }
        }
        std::string result;
        for (const auto& c : s) {
            if (std::isalpha(c)) {
                result.push_back(c);
            }
        }
        return result;
    }
};
