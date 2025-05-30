#include <stack>
#include <string>

/**
 * A parentheses string is a non-empty string consisting only of '(' and ')'. It is valid if any of
 * the following conditions is true:
 *
 * - It is ().
 *
 * - It can be written as AB (A concatenated with B), where A and B are valid parentheses strings.
 *
 * - It can be written as (A), where A is a valid parentheses string.
 *
 * You are given a parentheses string s and a string locked, both of length n. locked is a binary
 * string consisting only of '0's and '1's. For each index i of locked,
 *
 * - If locked[i] is '1', you cannot change s[i].
 *
 * - But if locked[i] is '0', you can change s[i] to either '(' or ')'.
 *
 * Return true if you can make s a valid parentheses string. Otherwise, return false.
 *
 * ! n == s.length == locked.length
 * ! 1 <= n <= 10^5
 * ! s[i] is either '(' or ')'.
 * ! locked[i] is either '0' or '1'.
 */

class Solution
{
public:
    bool canBeValid(std::string s, std::string locked)
    {
        const int n = s.size();
        if (n % 2)
            return false;

        std::stack<int> left;
        std::stack<int> unlocked;
        for (int i = 0; i < n; ++i) {
            if (locked[i] == '0') {
                unlocked.push(i);
                continue;
            }
            if (s[i] == '(') {
                left.push(i);
                continue;
            }
            if (!left.empty()) {
                left.pop();
            } else if (!unlocked.empty()) {
                unlocked.pop();
            } else {
                return false;
            }
        }
        while (!left.empty() && !unlocked.empty()) {
            if (left.top() > unlocked.top())
                return false;

            left.pop();
            unlocked.pop();
        }
        return left.empty();
    }
};