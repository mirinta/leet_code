#include <string>

/**
 * You are given a string s of even length. Split this string into two halves of equal lengths, and
 * let a be the first half and b be the second half.
 *
 * Two strings are alike if they have the same number of vowels ('a', 'e', 'i', 'o', 'u', 'A', 'E',
 * 'I', 'O', 'U'). Notice that s contains uppercase and lowercase letters.
 *
 * Return true if a and b are alike. Otherwise, return false.
 *
 * ! 2 <= s.length <= 1000
 * ! s.length is even.
 * ! s consists of uppercase and lowercase letters.
 */

class Solution {
public:
    bool halvesAreAlike(std::string s)
    {
        const int n = s.size();
        int first = 0;
        int second = 0;
        for (int i = 0; i < n; ++i) {
            if (!isVowel(s[i]))
                continue;

            if (i < n / 2) {
                first++;
            } else {
                second++;
            }
        }
        return first == second;
    }

private:
    bool isVowel(char c)
    {
        c = std::tolower(c);
        return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
    }
};