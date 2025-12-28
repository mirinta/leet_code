#include <string>

/**
 * You are given a string s consisting of lowercase English letters. A duplicate removal consists of
 * choosing two adjacent and equal letters and removing them.
 *
 * We repeatedly make duplicate removals on s until we no longer can.
 *
 * Return the final string after all such duplicate removals have been made. It can be proven that
 * the answer is unique.
 *
 * ! 1 <= s.length <= 10^5
 * ! s consists of lowercase English letters.
 */

class Solution {
public:
    std::string removeDuplicates(const std::string& s)
    {
        if (s.size() < 2)
            return s;

        std::string result;
        for (const auto& c : s) {
            if (result.empty() || result.back() != c) {
                result.push_back(c);
            } else {
                result.pop_back();
            }
        }
        return result;
    }
};