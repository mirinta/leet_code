#include <string>

/**
 * Given a string s, reverse the order of characters in each word within a sentence while still
 * preserving whitespace and initial word order.
 *
 * ! 1 <= s.length <= 5 * 10^4
 * ! s contains printable ASCII characters.
 * ! s does not contain any leading or trailing spaces.
 * ! There is at least one word in s.
 * ! All the words in s are separated by a single space.
 */

class Solution {
public:
    std::string reverseWords(std::string s)
    {
        const int n = s.size();
        std::string result(s);
        for (int left = 0, right = 0; right < n; ++right) {
            if (right < n - 1 && s[right] != ' ')
                continue;

            auto begin = std::next(result.begin(), left);
            auto end = right == n - 1 ? result.end() : std::next(result.begin(), right);
            std::reverse(begin, end);
            left = right + 1;
        }
        return result;
    }
};