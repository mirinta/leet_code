#include <algorithm>
#include <stack>
#include <string>
#include <vector>

/**
 * You are given a string s representing a list of words. Each letter in the word has one or more
 * options.
 *
 * - If there is one option, the letter is represented as is.
 *
 * - If there is more than one option, then curly braces delimit the options. For example, "{a,b,c}"
 * represents options ["a", "b", "c"].
 *
 * For example, if s = "a{b,c}", the first character is always 'a', but the second character can be
 * 'b' or 'c'. The original list is ["ab", "ac"].
 *
 * Return all words that can be formed in this manner, sorted in lexicographical order.
 *
 * ! 1 <= s.length <= 50
 * ! s consists of curly brackets '{}', commas ',', and lowercase English letters.
 * ! s is guaranteed to be a valid input.
 * ! There are no nested curly brackets.
 * ! All characters inside a pair of consecutive opening and ending curly brackets are different.
 */

class Solution {
public:
    std::vector<std::string> expand(std::string s)
    {
        std::vector<std::string> result;
        std::string path;
        backtrack(result, path, 0, preprocess(s));
        return result;
    }

private:
    std::vector<std::string> preprocess(const std::string& s)
    {
        std::vector<std::string> next;
        std::stack<char> stack;
        for (const auto& c : s) {
            if (c == ',')
                continue;

            if (c == '}') {
                std::string choices;
                while (!stack.empty() && stack.top() != '{') {
                    choices.push_back(stack.top());
                    stack.pop();
                }
                if (!stack.empty() && stack.top() == '{') {
                    stack.pop();
                }
                std::sort(choices.begin(), choices.end());
                next.push_back(std::move(choices));
            } else if (stack.empty() && std::isalpha(c)) {
                next.push_back(std::string(1, c));
            } else {
                stack.push(c);
            }
        }
        return next;
    }

    void backtrack(std::vector<std::string>& result, std::string& path, int i, const std::vector<std::string>& next)
    {
        if (i == next.size()) {
            result.push_back(path);
            return;
        }
        for (const auto& c : next[i]) {
            path.push_back(c);
            backtrack(result, path, i + 1, next);
            path.pop_back();
        }
    }
};