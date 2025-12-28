#include <algorithm>
#include <string>
#include <unordered_map>
#include <vector>

/**
 * You are given a 0-indexed string array words having length n and containing 0-indexed strings.
 *
 * You are allowed to perform the following operation any number of times (including zero):
 *
 * - Choose integers i, j, x, and y such that 0 <= i, j < n, 0 <= x < words[i].length, 0 <= y <
 * words[j].length, and swap the characters words[i][x] and words[j][y].
 *
 * Return an integer denoting the maximum number of palindromes words can contain, after performing
 * some operations.
 *
 * Note: i and j may be equal during an operation.
 *
 * ! 1 <= words.length <= 1000
 * ! 1 <= words[i].length <= 100
 * ! words[i] consists only of lowercase English letters.
 */

class Solution {
public:
    int maxPalindromesAfterOperations(std::vector<std::string>& words)
    {
        // shorter words are easier to be changed to palindromes
        // if s has even length, we need 2a + 2b or 4a, i.e., 2 character pairs
        // if s has odd length, we need 2a + 2b + c or 2a + c, i.e., 1 character pair + single
        // character
        std::unordered_map<char, int> map;
        for (const auto& word : words) {
            for (const auto& c : word) {
                map[c]++;
            }
        }
        int pairs = 0;
        for (const auto& [c, freq] : map) {
            pairs += freq / 2;
        }
        std::sort(words.begin(), words.end(), [](const auto& w1, const auto& w2) { return w1.size() < w2.size(); });
        int result = 0;
        for (const auto& word : words) {
            const int requirePairs = word.size() / 2;
            if (pairs < requirePairs)
                break;

            result++;
            pairs -= requirePairs;
        }
        return result;
    }
};