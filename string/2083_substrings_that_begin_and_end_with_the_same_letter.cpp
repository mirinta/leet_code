#include <array>
#include <string>

/**
 * You are given a 0-indexed string s consisting of only lowercase English letters. Return the
 * number of substrings in s that begin and end with the same character.
 *
 * A substring is a contiguous non-empty sequence of characters within a string.
 *
 * ! 1 <= s.length <= 10^5
 * ! s consists only of lowercase English letters.
 */

class Solution {
public:
    long long numberOfSubstrings(std::string s)
    {
        std::array<int, 26> count{};
        long long result = 0;
        for (const auto& c : s) {
            count[c - 'a']++;
            result += count[c - 'a'];
        }
        return result;
    }
};