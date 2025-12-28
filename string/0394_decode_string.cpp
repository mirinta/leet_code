#include <ranges>
#include <stack>
#include <string>

/**
 * Given an encoded string, return its decoded string.
 *
 * The encoding rule is: k[encoded_string], where the encoded_string inside the square brackets is
 * being repeated exactly k times. Note that k is guaranteed to be a positive integer.
 *
 * You may assume that the input string is always valid; there are no extra white spaces, square
 * brackets are well-formed, etc. Furthermore, you may assume that the original data does not
 * contain any digits and that digits are only for those repeat numbers, k. For example, there will
 * not be input like 3a or 2[4].
 *
 * The test cases are generated so that the length of the output will never exceed 105.
 *
 * ! 1 <= s.length <= 30
 * ! s consists of lowercase English letters, digits, and square brackets '[]'.
 * ! s is guaranteed to be a valid input.
 * ! All the integers in s are in the range [1, 300].
 */

class Solution {
public:
    std::string decodeString(std::string s)
    {
        std::stack<char> stack;
        for (const auto& c : s) {
            if (c != ']') {
                stack.push(c);
                continue;
            }
            // pattern = k[...]
            // parse repeated component (in reverse order)
            std::string component;
            while (!stack.empty() && stack.top() != '[') {
                component.push_back(stack.top());
                stack.pop();
            }
            stack.pop(); // pop '['
            // parse k
            int k = 0;
            int base = 1;
            while (!stack.empty() && std::isdigit(stack.top())) {
                k += (stack.top() - '0') * base;
                base *= 10;
                stack.pop();
            }
            // add component to stack and repeat k times
            for (int i = 0; i < k; ++i) {
                for (auto& iter : std::ranges::reverse_view(component)) {
                    stack.push(iter);
                }
            }
        }
        std::string result(stack.size(), ' ');
        for (int i = stack.size() - 1; i >= 0; --i) {
            result[i] = stack.top();
            stack.pop();
        }
        return result;
    }
};
