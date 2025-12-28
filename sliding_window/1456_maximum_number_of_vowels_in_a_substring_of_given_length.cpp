#include <string>

/**
 * Given a string s and an integer k, return the maximum number of vowel letters in any substring of
 * s with length k.
 *
 * Vowel letters in English are 'a', 'e', 'i', 'o', and 'u'.
 *
 * ! 1 <= s.length <= 105
 * !s consists of lowercase English letters.
 * !1 <= k <= s.length
 */

class Solution {
public:
    int maxVowels(std::string s, int k)
    {
        const int n = s.size();
        int count = 0;
        int result = 0;
        for (int i = 0; i < n; ++i) {
            count += isVowel(s[i]);
            if (i >= k) {
                count -= isVowel(s[i - k]);
            }
            result = std::max(result, count);
        }
        return result;
    }

private:
    bool isVowel(char c)
    {
        return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
    }
};