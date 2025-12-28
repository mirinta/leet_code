#include <stack>
#include <string>

/**
 * You are given a string s and two integers x and y. You can perform two types of operations any
 * number of times.
 *
 * - Remove substring "ab" and gain x points.
 * For example, when removing "ab" from "cabxbae" it becomes "cxbae".
 *
 * - Remove substring "ba" and gain y points.
 * For example, when removing "ba" from "cabxbae" it becomes "cabxe".
 *
 * Return the maximum points you can gain after applying the above operations on s.
 *
 * ! 1 <= s.length <= 10^5
 * ! 1 <= x, y <= 10^4
 * ! s consists of lowercase English letters.
 */

class Solution {
public:
    int maximumGain(std::string s, int x, int y)
    {
        std::pair<std::string, int> combo1{"ab", x};
        std::pair<std::string, int> combo2{"ba", y};
        if (y > x) {
            std::swap(combo1, combo2);
        }
        const auto [remain, score1] = solve(s, combo1);
        return score1 + solve(remain, combo2).second;
    }

private:
    std::pair<std::string, int> solve(const std::string& s, const std::pair<std::string, int>& combo)
    {
        const auto& [key, gain] = combo;
        std::stack<char> stack;
        int score = 0;
        for (const auto& c : s) {
            if (!stack.empty() && stack.top() == key[0] && c == key[1]) {
                score += gain;
                stack.pop();
            } else {
                stack.push(c);
            }
        }
        std::string remain(stack.size(), ' ');
        for (auto iter = remain.rbegin(); iter != remain.rend(); ++iter) {
            *iter = stack.top();
            stack.pop();
        }
        return {remain, score};
    }
};