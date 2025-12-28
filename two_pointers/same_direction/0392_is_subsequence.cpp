#include <string>

/**
 * Given two strings s and t, return true if s is a subsequence of t, or false otherwise.
 *
 * A subsequence of a string is a new string that is formed from the original string by deleting
 * some (can be none) of the characters without disturbing the relative positions of the remaining
 * characters. (i.e., "ace" is a subsequence of "abcde" while "aec" is not).
 *
 * ! 0 <= s.length <= 100
 * ! 0 <= t.length <= 10^4
 * ! s and t consist only of lowercase English letters.
 */

class Solution {
public:
    bool isSubsequence(std::string s, std::string t)
    {
        if (s.empty())
            return true;

        if (s.size() > t.size())
            return false;

        int i = 0;
        int j = 0;
        while (i < t.size()) {
            if (t[i] == s[j]) {
                j++;
            }
            if (j == s.size())
                return true;

            i++;
        }
        return false;
    }
};
