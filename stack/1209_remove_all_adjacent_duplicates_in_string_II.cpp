#include <stack>
#include <string>

/**
 * You are given a string s and an integer k, a k duplicate removal consists of choosing k adjacent and equal letters
 * from s and removing them, causing the left and right side of the deleted substring to concatenate together.
 *
 * We repeatedly make k duplicate removals on s until we no longer can.
 *
 * Return the final string after all such duplicate removals have been made. It is guaranteed that the answer is unique.
 *
 * ! 1 <= s.length <= 10^5
 * ! 2 <= k <= 10^4
 */

class Solution {
public:
    std::string removeDuplicates(std::string& s, int k)
    {
        std::stack<std::pair<char, int>> stack;
        for (const auto& c : s) {
            if (!stack.empty() && stack.top().first == c) {
                auto [character, count] = stack.top();
                stack.pop();
                count++;
                if (count >= k) {
                    count %= k;
                }
                if (count > 0) {
                    stack.emplace(character, count);
                }
            } else {
                stack.emplace(c, 1);
            }
        }
        std::string result;
        while (!stack.empty()) {
            const auto [c, count] = stack.top();
            stack.pop();
            result.append(count, c);
        }
        std::reverse(result.begin(), result.end());
        return result;
    }
};