#include <string>
#include <vector>

/**
 * You are given an array of strings words, where each string represents a word containing lowercase English letters.
 *
 * You are also given an integer array weights of length 26, where weights[i] represents the weight of the ith lowercase
 * English letter.
 *
 * The weight of a word is defined as the sum of the weights of its characters.
 *
 * For each word, take its weight modulo 26 and map the result to a lowercase English letter using reverse alphabetical
 * order (0 -> 'z', 1 -> 'y', ..., 26 -> 'a').
 *
 * Return a string formed by concatenating the mapped characters for all words in order.
 *
 * ! 1 <= words.length <= 100
 * ! 1 <= words[i].length <= 10
 * ! weights.length == 26
 * ! 1 <= weights[i] <= 100
 * ! words[i] consist of lowercase English letters.
 */

class Solution {
public:
    std::string mapWordWeights(std::vector<std::string>& words, std::vector<int>& weights)
    {
        std::string result;
        result.reserve(words.size());
        for (const auto& s : words) {
            int sum = 0;
            for (const auto& c : s) {
                sum += weights[c - 'a'];
            }
            result.push_back('z' - sum % 26);
        }
        return result;
    }
};