#include <string>

/**
 * You are given a string s and a character c. Return the total number of substrings of s that start
 * and end with c.
 *
 * ! 1 <= s.length <= 10^5
 * ! s and c consist only of lowercase English letters.
 */

class Solution {
public:
    long long countSubstrings(std::string s, char c)
    {
        long long count = 0;
        for (const auto& letter : s) {
            if (letter == c) {
                count++;
            }
        }
        return (count + 1) * count / 2;
    }
};