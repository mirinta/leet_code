#include <string>
#include <vector>

/**
 * Given an array of strings patterns and a string word, return the number of strings in patterns that exist as a
 * substring in word.
 *
 * A substring is a contiguous sequence of characters within a string.
 *
 * ! 1 <= patterns.length <= 100
 * ! 1 <= patterns[i].length <= 100
 * ! 1 <= word.length <= 100
 * ! patterns[i] and word consist of lowercase English letters.
 */

class Solution {
public:
    int numOfStrings(std::vector<std::string>& patterns, std::string& word)
    {
        int result = 0;
        for (const auto& s : patterns) {
            result += word.find(s) != std::string::npos;
        }
        return result;
    }
};