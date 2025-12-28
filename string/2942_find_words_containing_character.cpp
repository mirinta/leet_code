#include <string>
#include <vector>

/**
 * You are given a 0-indexed array of strings words and a character x.
 *
 * Return an array of indices representing the words that contain the character x.
 *
 * Note that the returned array may be in any order.
 *
 * ! 1 <= words.length <= 50
 * ! 1 <= words[i].length <= 50
 * ! x is a lowercase English letter.
 * ! words[i] consists only of lowercase English letters.
 */

class Solution {
public:
    std::vector<int> findWordsContaining(std::vector<std::string>& words, char x)
    {
        const int n = words.size();
        std::vector<int> result;
        for (int i = 0; i < n; ++i) {
            if (words[i].find(x) != std::string::npos) {
                result.push_back(i);
            }
        }
        return result;
    }
};