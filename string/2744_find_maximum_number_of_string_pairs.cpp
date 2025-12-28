#include <string>
#include <unordered_set>
#include <vector>

/**
 * You are given a 0-indexed array words consisting of distinct strings.
 *
 * The string words[i] can be paired with the string words[j] if:
 *
 * - The string words[i] is equal to the reversed string of words[j].
 *
 * - 0 <= i < j < words.length.
 *
 * Return the maximum number of pairs that can be formed from the array words.
 *
 * Note that each string can belong in at most one pair.
 *
 * ! 1 <= words.length <= 50
 * ! words[i].length == 2
 * ! words consists of distinct strings.
 * ! words[i] contains only lowercase English letters.
 */

class Solution {
public:
    int maximumNumberOfStringPairs(std::vector<std::string>& words)
    {
        if (words.size() < 2)
            return 0;

        int result = 0;
        std::unordered_set<std::string> set;
        for (const auto& word : words) {
            if (set.count(word) || set.count(std::string(word.rbegin(), word.rend()))) {
                result++;
            } else {
                set.insert(word);
            }
        }
        return result;
    }

private:
    int approach1(std::vector<std::string>& words)
    {
        if (words.size() < 2)
            return 0;

        // all strings are distinct
        // - if X and X' is a pair, then there is no other X or X' in the array
        // - i.e., if X can be paired, then there is only one pair
        // each string contains only two letters
        int result = 0;
        for (int i = 0; i < words.size(); ++i) {
            for (int j = i + 1; j < words.size(); ++j) {
                if (words[i][0] == words[j][1] && words[i][1] == words[j][0]) {
                    result++;
                }
            }
        }
        return result;
    }
};