#include <string>
#include <unordered_map>

/**
 * There is a special keyboard with all keys in a single row.
 *
 * Given a string keyboard of length 26 indicating the layout of the keyboard (indexed from 0 to
 * 25). Initially, your finger is at index 0. To type a character, you have to move your finger to
 * the index of the desired character. The time taken to move your finger from index i to index j is
 * |i - j|.
 *
 * You want to type a string word. Write a function to calculate how much time it takes to type it
 * with one finger.
 *
 * ! keyboard.length == 26
 * ! keyboard contains each English lowercase letter exactly once in some order.
 * ! 1 <= word.length <= 10^4
 * ! word[i] is an English lowercase letter.
 */

class Solution {
public:
    int calculateTime(std::string keyboard, std::string word)
    {
        std::unordered_map<char, int> map;
        for (int i = 0; i < keyboard.size(); ++i) {
            map[keyboard[i]] = i;
        }
        int result = 0;
        for (int i = 0, pos = 0; i < word.size(); ++i) {
            result += std::abs(map[word[i]] - pos);
            pos = map[word[i]];
        }
        return result;
    }
};
