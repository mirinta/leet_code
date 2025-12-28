#include <string>
#include <unordered_map>

/**
 * You are given a string word. A letter c is called special if it appears both in lowercase and
 * uppercase in word, and every lowercase occurrence of c appears before the first uppercase
 * occurrence of c.
 *
 * Return the number of special letters in word.
 *
 * ! 1 <= word.length <= 2 * 10^5
 * ! word consists of only lowercase and uppercase English letters.
 */

class Solution {
public:
    int numberOfSpecialChars(std::string word)
    {
        const int n = word.size();
        std::unordered_map<char, int> map;
        for (int i = 0; i < n; ++i) {
            if (std::islower(word[i]) || !map.count(word[i])) {
                map[word[i]] = i;
            }
        }
        int result = 0;
        for (int i = 0; i < 26; ++i) {
            const char lower = i + 'a';
            const char upper = std::toupper(lower);
            if (map.count(lower) && map.count(upper) && map[lower] < map[upper]) {
                result++;
            }
        }
        return result;
    }
};