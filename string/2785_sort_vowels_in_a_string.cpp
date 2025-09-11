#include <algorithm>
#include <string>
#include <unordered_map>

/**
 * Given a 0-indexed string s, permute s to get a new string t such that:
 *
 * - All consonants remain in their original places. More formally, if there is an index i with 0 <=
 * i < s.length such that s[i] is a consonant, then t[i] = s[i].
 *
 * - The vowels must be sorted in the nondecreasing order of their ASCII values. More formally, for
 * pairs of indices i, j with 0 <= i < j < s.length such that s[i] and s[j] are vowels, then t[i]
 * must not have a higher ASCII value than t[j].
 *
 * Return the resulting string.
 *
 * The vowels are 'a', 'e', 'i', 'o', and 'u', and they can appear in lowercase or uppercase.
 * Consonants comprise all letters that are not vowels.
 *
 * ! 1 <= s.length <= 10^5
 * ! s consists only of letters of the English alphabet in uppercase and lowercase.
 */

class Solution
{
public:
    std::string sortVowels(std::string s)
    {
        std::unordered_map<char, int> map;
        for (const auto& c : s) {
            if (isVowel(c)) {
                map[c]++;
            }
        }
        int i = 0;
        for (auto& c : s) {
            if (!isVowel(c))
                continue;

            while (i < kVowels.size() && map[kVowels[i]] == 0) {
                i++;
            }
            if (i < kVowels.size()) {
                c = kVowels[i];
                map[kVowels[i]]--;
            }
        }
        return s;
    }

private:
    static constexpr std::string_view kVowels{"AEIOUaeiou"};

    bool isVowel(char c)
    {
        c = std::tolower(c);
        return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
    }
};
