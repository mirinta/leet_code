#include <string>

/**
 * You are given a string s and a positive integer k.
 *
 * Let vowels and consonants be the number of vowels and consonants in a string.
 *
 * A string is beautiful if:
 *
 * - vowels == consonants.
 *
 * - (vowels * consonants) % k == 0, in other terms the multiplication of vowels and consonants is
 * divisible by k. Return the number of non-empty beautiful substrings in the given string s.
 *
 * A substring is a contiguous sequence of characters in a string.
 *
 * Vowel letters in English are 'a', 'e', 'i', 'o', and 'u'.
 *
 * Consonant letters in English are every letter except vowels.
 *
 * ! 1 <= s.length <= 1000
 * ! 1 <= k <= 1000
 * ! s consists of only English lowercase letters.
 */

class Solution {
public:
    int beautifulSubstrings(std::string s, int k)
    {
        const int n = s.size();
        int result = 0;
        for (int i = 0; i < n; ++i) {
            int vowels = 0;
            for (int j = i; j < n; ++j) {
                vowels += isVowel(s[j]);
                const int length = j - i + 1;
                if (2 * vowels == length && vowels * vowels % k == 0) {
                    result++;
                }
            }
        }
        return result;
    }

private:
    bool isVowel(char c)
    {
        return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
    }
};