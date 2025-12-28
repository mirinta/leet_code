#include <string>

/**
 * Given a string s, reverse only all the vowels in the string and return it.
 *
 * The vowels are 'a', 'e', 'i', 'o', and 'u', and they can appear in both lower and upper cases,
 * more than once.
 *
 * ! 1 <= s.length <= 3 * 10^5
 * ! s consist of printable ASCII characters.
 */

class Solution {
public:
    std::string reverseVowels(std::string s)
    {
        const int n = s.size();
        if (n <= 1)
            return s;

        int left = 0;
        int right = n - 1;
        while (true) {
            while (left < n && !isVowel(s[left])) {
                left++;
            }
            while (right >= 0 && !isVowel(s[right])) {
                right--;
            }
            if (left >= right)
                break;

            std::swap(s[left++], s[right--]);
        }
        return s;
    }

private:
    bool isVowel(char c)
    {
        c = std::tolower(c);
        return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
    }
};