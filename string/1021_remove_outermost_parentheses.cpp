#include <string>

/**
 * A valid parentheses string is either empty "", "(" + A + ")", or A + B, where A and B are valid parentheses strings,
 * and + represents string concatenation.
 *
 * - For example, "", "()", "(())()", and "(()(()))" are all valid parentheses strings.
 *
 * A valid parentheses string s is primitive if it is nonempty, and there does not exist a way to split it into s = A +
 * B, with A and B nonempty valid parentheses strings.
 *
 * Given a valid parentheses string s, consider its primitive decomposition: s = P1 + P2 + ... + Pk, where Pi are
 * primitive valid parentheses strings.
 *
 * Return s after removing the outermost parentheses of every primitive string in the primitive decomposition of s.
 *
 * ! 1 <= s.length <= 10^5
 * ! s[i] is either '(' or ')'.
 * ! s is a valid parentheses string.
 */

class Solution {
public:
    std::string removeOuterParentheses(std::string& s)
    {
        const int n = s.size();
        std::string result;
        for (int j = 0, i = 0, flag = 0; i < n; ++i) {
            flag += s[i] == '(' ? 1 : -1;
            if (flag == 0) {
                result += s.substr(j + 1, i - j - 1);
                j = i + 1;
            }
        }
        return result;
    }
};
