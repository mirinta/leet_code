#include <string>

/**
 * An alphabetical continuous string is a string consisting of consecutive letters in the alphabet.
 * In other words, it is any substring of the string "abcdefghijklmnopqrstuvwxyz".
 *
 * For example, "abc" is an alphabetical continuous string, while "acb" and "za" are not.
 *
 * Given a string s consisting of lowercase letters only, return the length of the longest
 * alphabetical continuous substring.
 *
 * ! 1 <= s.length <= 10^5
 * ! s consists of only English lowercase letters.
 */

class Solution {
public:
    int longestContinuousSubstring(std::string s)
    {
        const int n = s.size();
        int result = 1;
        for (int i = 1, count = 1; i < n; ++i) {
            if (s[i] - s[i - 1] == 1) {
                count++;
            } else {
                count = 1;
            }
            result = std::max(result, count);
        }
        return result;
    }
};
