#include <stack>
#include <string>
#include <vector>

/**
 * Given a string s of '(' , ')' and lowercase English characters.
 *
 * Your task is to remove the minimum number of parentheses ( '(' or ')', in any positions ) so that
 * the resulting parentheses string is valid and return any valid string.
 *
 * Formally, a parentheses string is valid if and only if:
 *
 * - It is the empty string, contains only lowercase characters, or
 *
 * - It can be written as AB (A concatenated with B), where A and B are valid strings, or
 *
 * - It can be written as (A), where A is a valid string.
 *
 * ! 1 <= s.length <= 10^5
 * ! s[i] is either'(' , ')', or lowercase English letter.
 */

class Solution {
public:
    std::string minRemoveToMakeValid(std::string s)
    {
        const int n = s.size();
        std::vector<bool> isValid(n, false);
        std::stack<int> stack;
        for (int i = 0; i < n; ++i) {
            if (std::isalpha(s[i])) {
                isValid[i] = true;
                continue;
            }
            if (s[i] == '(') {
                stack.push(i);
                continue;
            }
            if (s[i] == ')' && !stack.empty()) {
                isValid[i] = true;
                isValid[stack.top()] = true;
                stack.pop();
            }
        }
        std::string result;
        for (int i = 0; i < n; ++i) {
            if (isValid[i]) {
                result.push_back(s[i]);
            }
        }
        return result;
    }
};