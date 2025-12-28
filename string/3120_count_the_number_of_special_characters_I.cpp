#include <string>
#include <unordered_set>

/**
 * You are given a string word. A letter is called special if it appears both in lowercase and
 * uppercase in word.
 *
 * Return the number of special letters in word.
 *
 * ! 1 <= word.length <= 50
 * ! word consists of only lowercase and uppercase English letters.
 */

class Solution {
public:
    int numberOfSpecialChars(std::string word)
    {
        std::unordered_set<char> set(word.begin(), word.end());
        int result = 0;
        for (int i = 0; i < 26; ++i) {
            const char lower = i + 'a';
            const char upper = std::toupper(lower);
            if (set.count(lower) && set.count(upper)) {
                result++;
            }
        }
        return result;
    }
};