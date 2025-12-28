#include <string>

/**
 * A parentheses string is valid if and only if:
 *
 * - It is the empty string,
 *
 * - It can be written as AB (A concatenated with B), where A and B are valid strings, or
 *
 * - It can be written as (A), where A is a valid string.
 *
 * You are given a parentheses string s. In one move, you can insert a parenthesis at any position
 * of the string.
 *
 * - For example, if s = "()))", you can insert an opening parenthesis to be "(()))" or a closing
 * parenthesis to be "())))".
 *
 * Return the minimum number of moves required to make s valid.
 *
 * ! 1 <= s.length <= 1000
 * ! s[i] is either '(' or ')'.
 */

class Solution {
public:
    int minAddToMakeValid(std::string s)
    {
        int mismatchedLeft = 0;
        int result = 0;
        for (const auto& c : s) {
            if (c == '(') {
                mismatchedLeft++;
            } else {
                mismatchedLeft--;
            }
            if (mismatchedLeft < 0) {
                result++;
                mismatchedLeft = 0;
            }
        }
        result += mismatchedLeft;
        return result;
    }
};