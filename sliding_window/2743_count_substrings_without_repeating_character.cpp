#include <array>
#include <string>

/**
 * You are given a string s consisting only of lowercase English letters. We call a substring
 * special if it contains no character which has occurred at least twice (in other words, it does
 * not contain a repeating character). Your task is to count the number of special substrings. For
 * example, in the string "pop", the substring "po" is a special substring, however, "pop" is not
 * special (since 'p' has occurred twice).
 *
 * Return the number of special substrings.
 *
 * A substring is a contiguous sequence of characters within a string. For example, "abc" is a
 * substring of "abcd", but "acd" is not.
 *
 * ! 1 <= s.length <= 10^5
 * ! s consists of lowercase English letters
 */

class Solution {
public:
    int numberOfSpecialSubstrings(std::string s)
    {
        const int n = s.size();
        std::array<int, 26> count{};
        int result = 0;
        for (int left = 0, right = 0; right < n; ++right) {
            count[s[right] - 'a']++;
            while (count[s[right] - 'a'] > 1) {
                count[s[left] - 'a']--;
                left++;
            }
            result += right - left + 1;
        }
        return result;
    }
};