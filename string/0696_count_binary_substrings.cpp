#include <string>

/**
 * Given a binary string s, return the number of non-empty substrings that have the same number of 0's and 1's, and all
 * the 0's and all the 1's in these substrings are grouped consecutively.
 *
 * Substrings that occur multiple times are counted the number of times they occur.
 *
 * ! 1 <= s.length <= 10^5
 * ! s[i] is either '0' or '1'.
 */

class Solution {
public:
    int countBinarySubstrings(std::string& s)
    {
        const int n = s.size();
        int result = 0;
        for (int i = 1, curr = 1, prev = 0; i < n; ++i) {
            if (s[i] == s[i - 1]) {
                curr++;
            } else {
                prev = curr;
                curr = 1;
            }
            result += curr <= prev;
        }
        return result;
    }
};