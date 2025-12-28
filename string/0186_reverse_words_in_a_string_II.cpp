#include <string>
#include <vector>

/**
 * Given a character array s, reverse the order of the words.
 *
 * A word is defined as a sequence of non-space characters. The words in s will be separated by a
 * single space.
 *
 * Your code must solve the problem in-place, i.e. without allocating extra space.
 *
 * ! 1 <= s.length <= 10^5
 * ! s[i] is an English letter (uppercase or lowercase), digit, or space ' '.
 * ! There is at least one word in s.
 * ! s does not contain leading or trailing spaces.
 * ! All the words in s are guaranteed to be separated by a single space.
 */

class Solution {
public:
    void reverseWords(std::vector<char>& s)
    {
        // original: abc xyz
        // reverse1: zyx cba
        // reverse2: xyz abc
        const int n = s.size();
        std::reverse(s.begin(), s.end());
        int i = 0;
        while (i < n) {
            int j = i;
            while (j < n && s[j] != ' ') {
                j++;
            }
            std::reverse(s.begin() + i, s.begin() + j);
            i = j + 1;
        }
    }
};
