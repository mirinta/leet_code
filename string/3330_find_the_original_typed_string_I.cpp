#include <string>

/**
 * Alice is attempting to type a specific string on her computer. However, she tends to be clumsy
 * and may press a key for too long, resulting in a character being typed multiple times.
 *
 * Although Alice tried to focus on her typing, she is aware that she may still have done this at
 * most once.
 *
 * You are given a string word, which represents the final output displayed on Alice's screen.
 *
 * Return the total number of possible original strings that Alice might have intended to type.
 *
 * ! 1 <= word.length <= 100
 * ! word consists only of lowercase English letters.
 */

class Solution
{
public:
    int possibleStringCount(std::string word)
    {
        const int n = word.size();
        int i = 0;
        int result = 1;
        while (i < n) {
            int j = i + 1;
            while (j < n && word[j] == word[i]) {
                j++;
            }
            result += j - i - 1;
            i = j;
        }
        return result;
    }
};
