#include <string>
#include <unordered_set>
#include <vector>

/**
 * Given a string s that contains parentheses and letters, remove the minimum number of invalid
 * parentheses to make the input string valid.
 *
 * Return a list of unique strings that are valid with the minimum number of removals. You may
 * return the answer in any order.
 *
 * ! 1 <= s.length <= 25
 * ! s consists of lowercase English letters and parentheses '(' and ')'.
 * ! There will be at most 20 parentheses in s.
 */

class Solution {
public:
    std::vector<std::string> removeInvalidParentheses(const std::string& s)
    {
        int leftToRemove = 0;
        int rightToRemove = 0;
        for (const auto& c : s) {
            if (std::isalpha(c))
                continue;

            if (c == '(') {
                leftToRemove++;
            } else if (leftToRemove > 0) {
                leftToRemove--;
            } else {
                rightToRemove++;
            }
        }
        std::string path;
        backtrack(path, 0, leftToRemove, rightToRemove, 0, 0, s);
        return {unique.begin(), unique.end()};
    }

private:
    std::unordered_set<std::string> unique;

    void backtrack(std::string& path,
                   int i,
                   int leftToRemove,
                   int rightToRemove,
                   int leftCount,
                   int rightCount,
                   const std::string& s)
    {
        if (i == s.size()) {
            if (leftToRemove == 0 && rightToRemove == 0) {
                unique.insert(path);
            }
            return;
        }
        // case 1: remove s[i]
        if (s[i] == '(' && leftToRemove > 0) {
            backtrack(path, i + 1, leftToRemove - 1, rightToRemove, leftCount, rightCount, s);
        }
        if (s[i] == ')' && rightToRemove > 0) {
            backtrack(path, i + 1, leftToRemove, rightToRemove - 1, leftCount, rightCount, s);
        }
        // case 2: keep s[i]
        path.push_back(s[i]);
        if (std::isalpha(s[i])) {
            backtrack(path, i + 1, leftToRemove, rightToRemove, leftCount, rightCount, s);
        } else if (s[i] == '(') {
            backtrack(path, i + 1, leftToRemove, rightToRemove, leftCount + 1, rightCount, s);
        } else if (leftCount > rightCount) {
            backtrack(path, i + 1, leftToRemove, rightToRemove, leftCount, rightCount + 1, s);
        }
        path.pop_back();
    }
};