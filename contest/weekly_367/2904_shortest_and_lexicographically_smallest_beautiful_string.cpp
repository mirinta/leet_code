#include <string>

/**
 * You are given a binary string s and a positive integer k.
 *
 * A substring of s is beautiful if the number of 1's in it is exactly k.
 *
 * Let len be the length of the shortest beautiful substring.
 *
 * Return the lexicographically smallest beautiful substring of string s with length equal to len.
 * If s doesn't contain a beautiful substring, return an empty string.
 *
 * A string a is lexicographically larger than a string b (of the same length) if in the first
 * position where a and b differ, a has a character strictly larger than the corresponding character
 * in b.
 *
 * - For example, "abcd" is lexicographically larger than "abcc" because the first position they
 * differ is at the fourth character, and d is greater than c.
 *
 * ! 1 <= s.length <= 100
 * ! 1 <= k <= s.length
 */

class Solution
{
public:
    std::string shortestBeautifulSubstring(const std::string& s, int k)
    {
        const int n = s.size();
        int minLength = INT_MAX;
        std::string result;
        for (int left = 0, right = 0, count = 0; right < n; ++right) {
            count += s[right] == '1';
            while (count == k) {
                if (s[left] == '0') {
                    left++;
                    continue;
                }
                const int length = right - left + 1;
                if (length < minLength) {
                    minLength = length;
                    result = s.substr(left, length);
                } else if (length == minLength) {
                    result = std::min(result, s.substr(left, length));
                }
                count--;
                left++;
            }
        }
        return minLength == INT_MAX ? "" : result;
    }
};