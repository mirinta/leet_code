#include <stack>
#include <string>
#include <vector>

/**
 * You are given a string s and a robot that currently holds an empty string t. Apply one of the
 * following operations until s and t are both empty:
 *
 * - Remove the first character of a string s and give it to the robot. The robot will append this
 * character to the string t.
 *
 * - Remove the last character of a string t and give it to the robot. The robot will write this
 * character on paper.
 *
 * Return the lexicographically smallest string that can be written on the paper.
 *
 * ! 1 <= s.length <= 10^5
 * ! s consists of only English lowercase letters.
 */

class Solution {
public:
    std::string robotWithString(std::string s)
    {
        const int n = s.size();
        std::vector<char> nextSmallest(n, s.back());
        for (int i = n - 2; i >= 0; --i) {
            nextSmallest[i] = std::min(s[i], nextSmallest[i + 1]);
        }
        std::stack<char> stack;
        std::string result;
        result.reserve(n);
        for (int i = 0; i < n; ++i) {
            while (!stack.empty() && stack.top() <= nextSmallest[i]) {
                result.push_back(stack.top());
                stack.pop();
            }
            stack.push(s[i]);
        }
        while (!stack.empty()) {
            result.push_back(stack.top());
            stack.pop();
        }
        return result;
    }
};