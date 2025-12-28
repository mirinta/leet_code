#include <string>

/**
 * You are given two strings s and t consisting of only lowercase English letters.
 *
 * Return the minimum number of characters that need to be appended to the end of s so that t
 * becomes a subsequence of s.
 *
 * A subsequence is a string that can be derived from another string by deleting some or no
 * characters without changing the order of the remaining characters.
 *
 * ! 1 <= s.length, t.length <= 10^5
 * ! s and t consist only of lowercase English letters.
 */

class Solution {
public:
    int appendCharacters(std::string s, std::string t)
    {
        int i = 0;
        for (const auto& c : s) {
            if (i < t.size() && c == t[i]) {
                i++;
            }
        }
        return t.size() - i;
    }
};