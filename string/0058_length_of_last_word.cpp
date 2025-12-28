#include <string>

/**
 * Given a string "s" consisting of words and spaces, return the length of the last word in the
 * string.
 *
 * A word is a maximal substring consisting of non-space characters only.
 *
 * ! s consists of only English letters and spaces ' '.
 * ! There will be at least one word in "s".
 */

class Solution {
public:
    int lengthOfLastWord(const std::string& s)
    {
        const int n = s.size();
        int i = n - 1;
        while (i >= 0 && s[i] == ' ') {
            i--;
        }
        int j = i;
        while (j >= 0 && std::isalpha(s[j])) {
            j--;
        }
        return i - j;
    }
};