#include <stack>
#include <string>
#include <vector>

/**
 * You are given a string s, which contains stars *.
 *
 * In one operation, you can:
 *
 * - Choose a star in s.
 *
 * - Remove the closest non-star character to its left, as well as remove the star itself.
 *
 * Return the string after all stars have been removed.
 *
 * Note:
 *
 * - The input will be generated such that the operation is always possible.
 *
 * - It can be shown that the resulting string will always be unique.
 *
 * ! 1 <= s.length <= 10^5
 * ! s consists of lowercase English letters and stars *.
 * ! The operation above can be performed on s.
 */

class Solution {
public:
    std::string removeStars(std::string s)
    {
        std::stack<char> stack;
        for (const auto& c : s) {
            if (c != '*') {
                stack.push(c);
                continue;
            }
            if (!stack.empty() && c == '*') {
                stack.pop();
            }
        }
        std::string result(stack.size(), ' ');
        for (int i = result.size() - 1; i >= 0; --i) {
            result[i] = stack.top();
            stack.pop();
        }
        return result;
    }
};