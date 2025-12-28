#include <string>

/**
 * Given a string s, return the number of substrings that have only one distinct letter.
 *
 * ! 1 <= s.length <= 1000
 * ! s[i] consists of only lowercase English letters.
 */

class Solution {
public:
    int countLetters(std::string s)
    {
        const int n = s.size();
        int i = 0;
        int result = 0;
        while (i < n) {
            int j = i + 1;
            while (j < n && s[j] == s[i]) {
                j++;
            }
            const int length = j - i;
            result += (1 + length) * length / 2;
            i = j;
        }
        return result;
    }
};