#include <string>

/**
 * You are given a string s.
 *
 * Your task is to remove all digits by doing this operation repeatedly:
 *
 * - Delete the first digit and the closest non-digit character to its left.
 *
 * Return the resulting string after removing all digits.
 *
 * ! 1 <= s.length <= 100
 * ! s consists only of lowercase English letters and digits.
 * ! The input is generated such that it is possible to delete all digits.
 */

class Solution {
public:
    std::string clearDigits(std::string s)
    {
        const int n = s.size();
        std::string result;
        for (const auto& c : s) {
            if (std::isdigit(c) && !result.empty()) {
                result.pop_back();
                continue;
            }
            result.push_back(c);
        }
        return result;
    }
};