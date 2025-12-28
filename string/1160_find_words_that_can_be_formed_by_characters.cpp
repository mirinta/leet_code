#include <array>
#include <string>
#include <vector>

/**
 * You are given an array of strings words and a string chars.
 *
 * A string is good if it can be formed by characters from chars (each character can only be used
 * once).
 *
 * Return the sum of lengths of all good strings in words.
 *
 * ! 1 <= words.length <= 1000
 * ! 1 <= words[i].length, chars.length <= 100
 * ! words[i] and chars consist of lowercase English letters.
 */

class Solution {
public:
    int countCharacters(std::vector<std::string>& words, std::string chars)
    {
        std::array<int, 26> count{0};
        for (const auto& c : chars) {
            count[c - 'a']++;
        }
        int result = 0;
        for (const auto& word : words) {
            if (isGood(word, count)) {
                result += word.size();
            }
        }
        return result;
    }

private:
    bool isGood(const std::string& word, const std::array<int, 26>& count)
    {
        std::array<int, 26> freq{0};
        for (const auto& c : word) {
            const int index = c - 'a';
            if (count[index] == 0)
                return false;

            freq[index]++;
        }
        for (int i = 0; i < 26; ++i) {
            if (freq[i] > count[i])
                return false;
        }
        return true;
    }
};