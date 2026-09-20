#include <string>

/**
 * Given a string s, calculate its reverse degree.
 *
 * The reverse degree is calculated as follows:
 *
 * 1. For each character, multiply its position in the reversed alphabet ('a' = 26, 'b' = 25, ..., 'z' = 1) with its
 * position in the string (1-indexed).
 *
 * 2. Sum these product for all characters in the string.
 *
 * Return the reverse degree of s.
 *
 * ! 1 <= s.length <= 1000
 * ! s contains only lowercase English letters.
 */

class Solution {
public:
    int reverseDegree(std::string& s)
    {
        const int n = s.size();
        int result = 0;
        for (int i = 0; i < n; ++i) {
            result += (i + 1) * (26 - (s[i] - 'a'));
        }
        return result;
    }
};
