#include <string>

/**
 * You are given a 0-indexed binary string s having an even length.
 *
 * A string is beautiful if it's possible to partition it into one or more substrings such that:
 *
 * - Each substring has an even length.
 *
 * - Each substring contains only 1's or only 0's.
 *
 * You can change any character in s to 0 or 1.
 *
 * Return the minimum number of changes required to make the string s beautiful.
 *
 * ! 2 <= s.length <= 10^5
 * ! s has an even length.
 * ! s[i] is either '0' or '1'.
 */

class Solution {
public:
    int minChanges(std::string s)
    {
        // partition s into several substrings with length 2
        int result = 0;
        for (int i = 0; i < s.size(); i += 2) {
            if (s[i] != s[i + 1]) {
                result++;
            }
        }
        return result;
    }
};