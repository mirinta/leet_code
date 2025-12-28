#include <string>

/**
 * You are given a 0-indexed string s that consists of digits from 0 to 9.
 *
 * A string t is called a semi-repetitive if there is at most one consecutive pair of the same
 * digits inside t. For example, 0010, 002020, 0123, 2002, and 54944 are semi-repetitive while
 * 00101022, and 1101234883 are not.
 *
 * Return the length of the longest semi-repetitive substring inside s.
 *
 * A substring is a contiguous non-empty sequence of characters within a string.
 *
 * ! 1 <= s.length <= 50
 * ! '0' <= s[i] <= '9'
 */

class Solution {
public:
    int longestSemiRepetitiveSubstring(std::string s)
    {
        const int n = s.size();
        int pairs = 0;
        int result = 0;
        for (int left = 0, right = 0; right < n; ++right) {
            if (right > 0 && s[right] == s[right - 1]) {
                pairs++;
            }
            while (pairs > 1) {
                // we are about to move s[left] out of the window
                // so we need to check s[left] and s[left+1]
                if (left + 1 < n && s[left] == s[left + 1]) {
                    pairs--;
                }
                left++;
            }
            result = std::max(result, right - left + 1);
        }
        return result;
    }
};