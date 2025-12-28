#include <string>
#include <unordered_set>
#include <vector>

/**
 * You are given a string allowed consisting of distinct characters and an array of strings words. A
 * string is consistent if all characters in the string appear in the string allowed.
 *
 * Return the number of consistent strings in the array words.
 *
 * ! 1 <= words.length <= 10^4
 * ! 1 <= allowed.length <= 26
 * ! 1 <= words[i].length <= 10
 * ! The characters in allowed are distinct.
 * ! words[i] and allowed contain only lowercase English letters.
 */

class Solution {
public:
    int countConsistentStrings(std::string allowed, std::vector<std::string>& words)
    {
        std::unordered_set<char> set(allowed.begin(), allowed.end());
        int result = 0;
        for (const auto& word : words) {
            bool isValid = true;
            for (const auto& c : word) {
                if (!set.count(c)) {
                    isValid = false;
                    break;
                }
            }
            result += isValid;
        }
        return result;
    }
};