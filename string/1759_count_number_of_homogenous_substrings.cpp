#include <string>

/**
 * Given a string s, return the number of homogenous substrings of s. Since the answer may be too
 * large, return it modulo 10^9 + 7.
 *
 * A string is homogenous if all the characters of the string are the same.
 *
 * A substring is a contiguous sequence of characters within a string.
 *
 * ! 1 <= s.length <= 10^5
 * ! s consists of lowercase letters.
 */

class Solution {
public:
    int countHomogenous(std::string s)
    {
        constexpr int kMod = 1e9 + 7;
        int count = 0;
        int result = 0;
        for (int i = 0; i < s.size(); ++i) {
            if (i == 0 || s[i] == s[i - 1]) {
                count++;
            } else {
                count = 1;
            }
            result = (result + count) % kMod;
        }
        return result;
    }
};
