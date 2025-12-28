#include <array>
#include <stack>
#include <string>

/**
 * Given a string s, return the lexicographically smallest subsequence of s that contains all the
 * distinct characters of s exactly once.
 *
 * ! 1 <= s.length <= 1000
 * ! s consists of lowercase English letters.
 *
 * ! This question is the same as LC.316.
 */

class Solution {
public:
    std::string smallestSubsequence(std::string s)
    {
        const int n = s.size();
        std::array<int, 26> last{};
        last.fill(-1);
        for (int i = 0; i < n; ++i) {
            last[s[i] - 'a'] = i;
        }
        std::array<int, 26> inStack{};
        inStack.fill(false);
        std::stack<int> stack;
        for (int i = 0; i < n; ++i) {
            if (inStack[s[i] - 'a'])
                continue;

            while (!stack.empty() && s[i] < s[stack.top()] && last[s[stack.top()] - 'a'] > i) {
                const int top = stack.top();
                stack.pop();
                inStack[s[top] - 'a'] = false;
            }
            stack.push(i);
            inStack[s[i] - 'a'] = true;
        }
        std::string result(stack.size(), ' ');
        for (int i = result.size() - 1; i >= 0; --i) {
            result[i] = s[stack.top()];
            stack.pop();
        }
        return result;
    }
};
