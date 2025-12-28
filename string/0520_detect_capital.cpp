#include <string>

/**
 * We define the usage of capitals in a word to be right when one of the following cases holds:
 *
 * - All letters in this word are capitals, like "USA".
 *
 * - All letters in this word are not capitals, like "leetcode".
 *
 * - Only the first letter in this word is capital, like "Google".
 *
 * Given a string word, return true if the usage of capitals in it is right.
 *
 * ! 1 <= word.length <= 100
 * ! word consists of lowercase and uppercase English letters.
 */

class Solution {
public:
    bool detectCapitalUse(std::string word)
    {
        if (word.size() == 1)
            return true;

        const int n = word.size();
        for (int i = 1; i < n; ++i) {
            if (std::isupper(word[i]) ^ std::isupper(word[1]))
                return false;
        }
        if (std::islower(word[0]) && std::islower(word[1]))
            return true;

        return std::isupper(word[0]);
    }
};