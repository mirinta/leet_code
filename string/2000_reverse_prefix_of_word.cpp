#include <string>

/**
 * Given a 0-indexed string word and a character ch, reverse the segment of word that starts at
 * index 0 and ends at the index of the first occurrence of ch (inclusive). If the character ch does
 * not exist in word, do nothing.
 *
 * For example, if word = "abcdefd" and ch = "d", then you should reverse the segment that starts at
 * 0 and ends at 3 (inclusive). The resulting string will be "dcbaefd". Return the resulting string.
 *
 * ! 1 <= word.length <= 250
 * ! word consists of lowercase English letters.
 * ! ch is a lowercase English letter.
 */

class Solution {
public:
    std::string reversePrefix(std::string word, char ch)
    {
        const int n = word.size();
        for (int i = 0; i < n; ++i) {
            if (word[i] == ch) {
                std::reverse(word.begin(), word.begin() + i + 1);
                break;
            }
        }
        return word;
    }
};