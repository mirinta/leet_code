#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

/**
 * We can represent a sentence as an array of words, for example, the sentence "I am happy with
 * leetcode" can be represented as arr = ["I","am",happy","with","leetcode"].
 *
 * Given two sentences sentence1 and sentence2 each represented as a string array and given an array
 * of string pairs similarPairs where similarPairs[i] = [xi, yi] indicates that the two words xi and
 * yi are similar.
 *
 * Return true if sentence1 and sentence2 are similar, or false if they are not similar.
 *
 * Two sentences are similar if:
 *
 * - They have the same length (i.e., the same number of words)
 *
 * - sentence1[i] and sentence2[i] are similar.
 *
 * Notice that a word is always similar to itself, also notice that the similarity relation is not
 * transitive. For example, if the words a and b are similar, and the words b and c are similar, a
 * and c are not necessarily similar.
 *
 * ! 1 <= sentence1.length, sentence2.length <= 1000
 * ! 1 <= sentence1[i].length, sentence2[i].length <= 20
 * ! sentence1[i] and sentence2[i] consist of English letters.
 * ! 0 <= similarPairs.length <= 1000
 * ! similarPairs[i].length == 2
 * ! 1 <= xi.length, yi.length <= 20
 * ! xi and yi consist of lower-case and upper-case English letters.
 * ! All the pairs (xi, yi) are distinct.
 */

class Solution {
public:
    bool areSentencesSimilar(std::vector<std::string>& sentence1,
                             std::vector<std::string>& sentence2,
                             std::vector<std::vector<std::string>>& similarPairs)
    {
        if (sentence1.size() != sentence2.size())
            return false;

        std::unordered_map<std::string, std::unordered_set<std::string>> map;
        for (const auto& pair : similarPairs) {
            map[pair[0]].insert(pair[1]);
        }
        for (int i = 0; i < sentence1.size(); ++i) {
            const auto& word1 = sentence1[i];
            const auto& word2 = sentence2[i];
            if (word1 == word2)
                continue;

            const bool case1 = map.count(word1) && map[word1].count(word2);
            const bool case2 = map.count(word2) && map[word2].count(word1);
            if (!case1 && !case2)
                return false;
        }
        return true;
    }
};
