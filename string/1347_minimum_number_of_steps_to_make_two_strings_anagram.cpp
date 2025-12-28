#include <array>
#include <string>

/**
 * You are given two strings of the same length s and t. In one step you can choose any character of
 * t and replace it with another character.
 *
 * Return the minimum number of steps to make t an anagram of s.
 *
 * An Anagram of a string is a string that contains the same characters with a different (or the
 * same) ordering.
 *
 * ! 1 <= s.length <= 5 * 10^4
 * ! s.length == t.length
 * ! s and t consist of lowercase English letters only.
 */

class Solution {
public:
    int minSteps(std::string s, std::string t)
    {
        const int n = s.size();
        std::array<int, 26> freq{0};
        for (int i = 0; i < n; ++i) {
            freq[s[i] - 'a']++;
            freq[t[i] - 'a']--;
        }
        int result = 0;
        for (const auto& val : freq) {
            if (val > 0) {
                result += val;
            }
        }
        return result;
    }
};