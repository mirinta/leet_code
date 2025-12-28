#include <string>

/**
 * Given a string s consisting of lowercase English letters. Perform the following operation:
 *
 * Select any non-empty substring then replace every letter of the substring with the preceding
 * letter of the English alphabet.
 *
 * - For example, 'b' is converted to 'a', and 'a' is converted to 'z'.
 *
 * Return the lexicographically smallest string after performing the operation.
 *
 * ! 1 <= s.length <= 3 * 10^5
 * ! s consists of lowercase English letters
 */

class Solution {
public:
    std::string smallestString(std::string s)
    {
        const int n = s.size();
        int i = 0;
        for (; i < n; ++i) {
            if (s[i] != 'a')
                break;
        }
        if (i == n) {
            s[n - 1] = 'z';
            return s;
        }
        for (; i < n && s[i] != 'a'; ++i) {
            s[i] -= 1;
        }
        return s;
    }
};