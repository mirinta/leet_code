#include <string>

/**
 * Given a string s, remove the vowels 'a', 'e', 'i', 'o', and 'u' from it, and return the new
 * string.
 *
 * ! 1 <= s.length <= 1000
 * ! s consists of only lowercase English letters.
 */

class Solution {
public:
    std::string removeVowels(std::string s)
    {
        std::string result;
        for (const auto& c : s) {
            if (!isVowel(c)) {
                result.push_back(c);
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