#include <string>

/**
 * You are given a string s. The score of a string is defined as the sum of the absolute difference
 * between the ASCII values of adjacent characters.
 *
 * Return the score of s.
 *
 * ! 2 <= s.length <= 100
 * ! s consists only of lowercase English letters.
 */

class Solution {
public:
    int scoreOfString(std::string s)
    {
        const int n = s.size();
        int result = 0;
        for (int i = 0; i + 1 < n; ++i) {
            result += std::abs(s[i] - s[i + 1]);
        }
        return result;
    }
};