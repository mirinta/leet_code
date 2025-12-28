#include <stack>
#include <string>

/**
 * Given a string s containing only three types of characters: '(', ')' and '*', return true if s is
 * valid.
 *
 * The following rules define a valid string:
 *
 * - Any left parenthesis '(' must have a corresponding right parenthesis ')'.
 *
 * - Any right parenthesis ')' must have a corresponding left parenthesis '('.
 *
 * - Left parenthesis '(' must go before the corresponding right parenthesis ')'.
 *
 * - '*' could be treated as a single right parenthesis ')' or a single left parenthesis '(' or an
 * empty string "".
 *
 * ! 1 <= s.length <= 100
 * ! s[i] is '(', ')' or '*'.
 */

class Solution {
public:
    bool checkValidString(std::string s)
    {
        const int n = s.size();
        std::stack<int> left;
        std::stack<int> star;
        for (int i = 0; i < n; ++i) {
            if (s[i] == '(') {
                left.push(i);
            } else if (s[i] == '*') {
                star.push(i);
            } else if (!left.empty()) {
                left.pop();
            } else if (!star.empty()) {
                star.pop();
            } else {
                return false;
            }
        }
        while (!left.empty() && !star.empty()) {
            if (left.top() > star.top())
                return false;

            left.pop();
            star.pop();
        }
        return left.empty();
    }
};