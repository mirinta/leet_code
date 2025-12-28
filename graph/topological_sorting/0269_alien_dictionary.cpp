#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

/**
 * There is a new alien language that uses the English alphabet. However, the order among the
 * letters is unknown to you.
 *
 * You are given a list of strings words from the alien language's dictionary, where the strings in
 * words are sorted lexicographically by the rules of this new language.
 *
 * Return a string of the unique letters in the new alien language sorted in lexicographically
 * increasing order by the new language's rules. If there is no solution, return "". If there are
 * multiple solutions, return any of them.
 *
 * ! 1 <= words.length <= 100
 * ! 1 <= words[i].length <= 100
 * ! words[i] consists of only lowercase English letters.
 */

class Solution {
public:
    std::string alienOrder(std::vector<std::string>& words)
    {
        std::unordered_map<char, std::string> graph;
        std::unordered_map<char, int> indegrees;
        for (const auto& word : words) {
            for (const auto& c : word) {
                graph[c] = "";
                indegrees[c] = 0;
            }
        }
        for (int i = 0; i < words.size() - 1; ++i) {
            const auto& word1 = words[i];
            const auto& word2 = words[i + 1];
            if (word1.size() > word2.size() && word1.substr(0, word2.size()) == word2)
                return {}; // word2 is the prefix of word1, wrong order

            for (int j = 0; j < std::min(word1.size(), word2.size()); ++j) {
                if (word1[j] != word2[j]) {
                    graph[word1[j]].push_back(word2[j]);
                    indegrees[word2[j]]++;
                    break;
                }
            }
        }
        std::queue<char> queue;
        for (const auto& [c, indegree] : indegrees) {
            if (indegree == 0) {
                queue.push(c);
            }
        }
        std::string result;
        while (!queue.empty()) {
            const auto v = queue.front();
            queue.pop();
            result.push_back(v);
            for (const auto& w : graph[v]) {
                if (--indegrees[w] == 0) {
                    queue.push(w);
                }
            }
        }
        return result.size() == graph.size() ? result : "";
    }
};
