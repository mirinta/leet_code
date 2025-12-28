#include <array>
#include <string>
#include <vector>

/**
 * Given a string containing digits from "2-9" inclusive, return all possible letter combinations
 * that the number could represent. Return the answer in any order.
 *
 * A mapping of digits to letters (just like on the telephone buttons) is given below. Note that 1
 * does not map to any letters.
 *
 * ! 0 <= digits.length <= 4
 * ! digits[i] is a digit in the range ['2', '9'].
 */

class Solution {
public:
    std::vector<std::string> letterCombinations(std::string digits)
    {
        if (digits.empty())
            return {};

        std::vector<std::string> result;
        std::string current;
        backtrack(result, current, 0, digits);
        return result;
    }

private:
    const std::array<std::string, 10> kLetters{"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};

    void backtrack(std::vector<std::string>& result, std::string& current, int i, const std::string& digits)
    {
        if (i == digits.size()) {
            result.push_back(current);
            return;
        }
        for (const auto& c : kLetters[digits[i] - '0']) {
            current.push_back(c);
            backtrack(result, current, i + 1, digits);
            current.pop_back();
        }
    }
};
