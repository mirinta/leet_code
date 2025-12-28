#include <string>
#include <vector>

/**
 * Given a string s, you can transform every letter individually to be lowercase or uppercase to
 * create another string.
 *
 * Return a list of all possible strings we could create. Return the output in any order.
 *
 * ! 1 <= s.length <= 12
 * ! s consists of lowercase English letters, uppercase English letters, and digits.
 */

class Solution {
public:
    std::vector<std::string> letterCasePermutation(const std::string& s)
    {
        std::string permutation;
        backtrack(permutation, 0, s);
        return result;
    }

private:
    std::vector<std::string> result;

    void backtrack(std::string& permutation, int i, const std::string& s)
    {
        if (i == s.size()) {
            result.push_back(permutation);
            return;
        }
        std::string choices;
        if (std::isdigit(s[i])) {
            choices.push_back(s[i]);
        } else {
            choices.push_back(std::toupper(s[i]));
            choices.push_back(std::tolower(s[i]));
        }
        for (const auto& c : choices) {
            permutation.push_back(c);
            backtrack(permutation, i + 1, s);
            permutation.pop_back();
        }
    }
};