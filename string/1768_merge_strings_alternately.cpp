#include <string>

/**
 * You are given two strings "word1" and "word2". Merge the strings by adding letters in alternating
 * order, starting with "word1". If a string is longer than the other, append the additional letters
 * onto the end of the merged string.
 *
 * Return the merged string.
 */

class Solution {
public:
    std::string mergeAlternately(const std::string& word1, const std::string& word2)
    {
        const int n1 = word1.size();
        const int n2 = word2.size();
        std::string result(n1 + n2, ' ');
        bool flag = true; // use characters of word1
        for (int k = 0, i = 0, j = 0; k < result.size(); ++k) {
            if (i == n1) {
                result[k] = word2[j++];
                continue;
            }
            if (j == n2) {
                result[k] = word1[i++];
                continue;
            }
            result[k] = flag ? word1[i++] : word2[j++];
            flag ^= true;
        }
        return result;
    }
};