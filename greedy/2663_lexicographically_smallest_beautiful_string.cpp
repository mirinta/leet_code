#include <string>

/**
 * A string is beautiful if:
 *
 * - It consists of the first k letters of the English lowercase alphabet.
 *
 * - It does not contain any substring of length 2 or more which is a palindrome.
 *
 * You are given a beautiful string s of length n and a positive integer k.
 *
 * Return the lexicographically smallest string of length n, which is larger than s and is
 * beautiful. If there is no such string, return an empty string.
 *
 * A string a is lexicographically larger than a string b (of the same length) if in the first
 * position where a and b differ, a has a character strictly larger than the corresponding character
 * in b.
 *
 * - For example, "abcd" is lexicographically larger than "abcc" because the first position they
 * differ is at the fourth character, and d is greater than c.
 *
 * ! 1 <= n == s.length <= 105
 * ! 4 <= k <= 26
 * ! s is a beautiful string.
 */

class Solution {
public:
    std::string smallestBeautifulString(std::string s, int k)
    {
        const int n = s.size();
        // to get the lexicographically smaller string which is
        // larger than s, we need to find the largest index i such that
        // we can change s[i] and make s' to be a new valid string
        for (int i = n - 1; i >= 0; --i) {
            bool found = false;
            for (int c = s[i] + 1; c < 'a' + k; ++c) {
                if (!isValid(c, i, s))
                    continue;

                // greedily build s[i+1:n-1]
                s[i] = c;
                for (int j = i + 1; j < n; ++j) {
                    for (int x = 'a'; x < 'a' + k; ++x) {
                        if (!isValid(x, j, s))
                            continue;

                        s[j] = x;
                        break;
                    }
                }
                found = true;
                break;
            }
            if (found)
                return s;
        }
        return {};
    }

private:
    // since s is a valid string,
    // then any substring of s must be valid
    //
    // given a valid string s[0:i-1],
    // check if s[0:i] is a valid string if s[i] = c
    //
    // ... i-3 i-2 i-1 i
    //
    // we only need to consider all substrings ending at s[i]
    // - length = 2, if s[i-1:i] is not a palindrome, then s[i-1] != s[i]
    // - length = 3, if s[i-2:i] is not a palindrome, then s[i-2] != s[i]
    // - length >= 4, since s[0:i-1] is a valid string, then s[i-1] != s[i-2] is guaranteed
    //   which means there is no palindrome of length >= 4 which is ending at s[i]
    bool isValid(char c, int i, const std::string& s)
    {
        if (i - 1 >= 0 && s[i - 1] == c)
            return false;

        if (i - 2 >= 0 && s[i - 2] == c)
            return false;

        return true;
    }
};