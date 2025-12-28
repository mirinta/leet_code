#include <string>

/**
 * Given a string s consisting only of characters 'a', 'b', and 'c'. You are asked to apply the
 * following algorithm on the string any number of times:
 *
 * 1. Pick a non-empty prefix from the string s where all the characters in the prefix are equal.
 *
 * 2. Pick a non-empty suffix from the string s where all the characters in this suffix are equal.
 *
 * 3. The prefix and the suffix should not intersect at any index.
 *
 * 4. The characters from the prefix and suffix must be the same.
 *
 * 5. Delete both the prefix and the suffix.
 *
 * Return the minimum length of s after performing the above operation any number of times (possibly
 * zero times).
 *
 * ! 1 <= s.length <= 10^5
 * ! s only consists of characters 'a', 'b', and 'c'.
 */

class Solution {
public:
    int minimumLength(std::string s)
    {
        const int n = s.size();
        int i = 0;
        int j = n - 1;
        while (i < j && s[i] == s[j]) {
            const char c = s[i];
            while (i < j && s[i] == c) {
                i++;
            }
            while (j >= i && s[j] == c) {
                j--;
            }
        }
        return j - i + 1;
    }
};