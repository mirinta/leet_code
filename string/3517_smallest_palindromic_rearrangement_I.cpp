#include <array>
#include <string>

/**
 * You are given a palindromic string s.
 *
 * Return the lexicographically smallest palindromic permutation of s.
 *
 * ! 1 <= s.length <= 10^5
 * ! s consists of lowercase English letters.
 * ! s is guaranteed to be palindromic.
 */

class Solution {
public:
    std::string smallestPalindrome(std::string& s)
    {
        const int n = s.size();
        std::array<int, 26> count{};
        for (int i = 0; i < n / 2; ++i) {
            count[s[i] - 'a']++;
        }
        std::string result = s;
        for (int i = 0, L = 0, R = n - 1; i < 26; ++i) {
            if (count[i] == 0)
                continue;

            while (count[i]--) {
                result[L++] = i + 'a';
                result[R--] = i + 'a';
            }
        }
        return result;
    }
};