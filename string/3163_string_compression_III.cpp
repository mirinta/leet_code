#include <string>

/**
 * Given a string word, compress it using the following algorithm:
 *
 * - Begin with an empty string comp. While word is not empty, use the following operation:
 *
 *   Remove a maximum length prefix of word made of a single character c repeating at most 9 times.
 *
 * - Append the length of the prefix followed by c to comp.
 *
 * Return the string comp.
 *
 * ! 1 <= word.length <= 2 * 10^5
 * ! word consists only of lowercase English letters.
 */

class Solution {
public:
    std::string compressedString(std::string word)
    {
        const int n = word.size();
        std::string result;
        int i = 0;
        while (i < n) {
            int j = i + 1;
            while (j < n && word[j] == word[i]) {
                j++;
            }
            const int length = j - i;
            for (int k = 1; k <= length / 9; ++k) {
                result.push_back('9');
                result.push_back(word[i]);
            }
            if (length % 9 != 0) {
                result.push_back(length % 9 + '0');
                result.push_back(word[i]);
            }
            i = j;
        }
        return result;
    }
};