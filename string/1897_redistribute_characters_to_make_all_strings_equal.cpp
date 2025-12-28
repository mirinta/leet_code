#include <string>
#include <unordered_map>
#include <vector>

/**
 * You are given an array of strings words (0-indexed).
 *
 * In one operation, pick two distinct indices i and j, where words[i] is a non-empty string, and
 * move any character from words[i] to any position in words[j].
 *
 * Return true if you can make every string in words equal using any number of operations, and false
 * otherwise.
 *
 * ! 1 <= words.length <= 100
 * ! 1 <= words[i].length <= 100
 * ! words[i] consists of lowercase English letters.
 */

class Solution {
public:
    bool makeEqual(std::vector<std::string>& words)
    {
        const int n = words.size();
        std::unordered_map<char, int> map;
        for (const auto& word : words) {
            for (const auto& c : word) {
                map[c]++;
            }
        }
        for (const auto& [c, freq] : map) {
            if (freq % n != 0)
                return false;
        }
        return true;
    }
};