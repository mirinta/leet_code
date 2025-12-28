#include <string>

/**
 * A fancy string is a string where no three consecutive characters are equal.
 *
 * Given a string s, delete the minimum possible number of characters from s to make it fancy.
 *
 * Return the final string after the deletion. It can be shown that the answer will always be
 * unique.
 *
 * ! 1 <= s.length <= 10^5
 * ! s consists only of lowercase English letters.
 */

class Solution {
public:
    std::string makeFancyString(std::string s)
    {
        const int n = s.size();
        int i = 0;
        std::string result;
        while (i < n) {
            int j = i + 1;
            while (j < n && s[i] == s[j]) {
                j++;
            }
            result.push_back(s[i]);
            if (j - i >= 2) {
                result.push_back(s[i]);
            }
            i = j;
        }
        return result;
    }
};