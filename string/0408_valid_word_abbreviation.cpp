#include <string>

/**
 * A string can be abbreviated by replacing any number of non-adjacent, non-empty substrings with
 * their lengths. The lengths should not have leading zeros.
 *
 * For example, a string such as "substitution" could be abbreviated as (but not limited to):
 *
 * -  "s10n" ("s ubstitutio n")
 *
 * -  "sub4u4" ("sub stit u tion")
 *
 * -  "12" ("substitution")
 *
 * -  "su3i1u2on" ("su bst i t u ti on")
 *
 * -  "substitution" (no substrings replaced)
 *
 * The following are not valid abbreviations:
 *
 * -  "s55n" ("s ubsti tutio n", the replaced substrings are adjacent)
 *
 * -  "s010n" (has leading zeros)
 *
 * - "s0ubstitution" (replaces an empty substring)
 *
 * Given a string word and an abbreviation abbr, return whether the string matches the given
 * abbreviation.
 *
 * A substring is a contiguous non-empty sequence of characters within a string.
 *
 * ! 1 <= word.length <= 20
 * ! word consists of only lowercase English letters.
 * ! 1 <= abbr.length <= 10
 * ! abbr consists of lowercase English letters and digits.
 * ! All the integers in abbr will fit in a 32-bit integer.
 */

class Solution {
public:
    bool validWordAbbreviation(std::string word, std::string abbr)
    {
        const int n = word.size();
        const int m = abbr.size();
        int i = 0;
        int j = 0;
        while (i < m) {
            if (!std::isdigit(abbr[i]) && (abbr[i] > 'z' || abbr[i] < 'a'))
                return false;

            if (std::isalpha(abbr[i])) {
                if (j >= n || abbr[i] != word[j])
                    return false;

                i++;
                j++;
                continue;
            }
            if (abbr[i] == '0')
                return false;

            int val = 0;
            while (i < m && std::isdigit(abbr[i])) {
                val = val * 10 + (abbr[i] - '0');
                if (val > n - j)
                    return false;

                i++;
            }
            j += val;
        }
        return i == m && j == n;
    }
};