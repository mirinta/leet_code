#include <string>
#include <vector>

/**
 * Given an array of string words, return all strings in words that is a substring of another word.
 * You can return the answer in any order.
 *
 * A substring is a contiguous sequence of characters within a string
 *
 * ! 1 <= words.length <= 100
 * ! 1 <= words[i].length <= 30
 * ! words[i] contains only lowercase English letters.
 * ! All the strings of words are unique.
 */

class Solution {
public:
    std::vector<std::string> stringMatching(std::vector<std::string>& words)
    {
        const int n = words.size();
        std::vector<std::string> result;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (j != i && words[j].find(words[i]) != std::string::npos) {
                    result.push_back(words[i]);
                    break;
                }
            }
        }
        return result;
    }
};
