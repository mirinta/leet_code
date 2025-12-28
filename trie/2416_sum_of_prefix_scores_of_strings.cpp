#include <array>
#include <string>
#include <vector>

/**
 * You are given an array words of size n consisting of non-empty strings.
 *
 * We define the score of a string term as the number of strings words[i] such that term is a prefix
 * of words[i].
 *
 * For example, if words = ["a", "ab", "abc", "cab"], then the score of "ab" is 2, since "ab" is a
 * prefix of both "ab" and "abc". Return an array answer of size n where answer[i] is the sum of
 * scores of every non-empty prefix of words[i].
 *
 * Note that a string is considered as a prefix of itself.
 *
 * ! 1 <= words.length <= 1000
 * ! 1 <= words[i].length <= 1000
 * ! words[i] consists of lowercase English letters.
 */

class Trie {
public:
    explicit Trie() : root(new TrieNode) {}

    void insert(const std::string& s)
    {
        auto* node = root;
        for (const auto& c : s) {
            const int index = c - 'a';
            if (!node->next[index]) {
                node->next[index] = new TrieNode;
            }
            node = node->next[index];
            node->count++;
        }
    }

    int score(const std::string& s)
    {
        auto* node = root;
        int sum = 0;
        for (const auto& c : s) {
            const int index = c - 'a';
            if (!node->next[index])
                break;

            node = node->next[index];
            sum += node->count;
        }
        return sum;
    }

private:
    struct TrieNode {
        int count{0};
        std::array<TrieNode*, 26> next{};
    };

    TrieNode* root;
};

class Solution {
public:
    std::vector<int> sumPrefixScores(std::vector<std::string>& words)
    {
        // let s = "abc",
        // prefix "a", #count1 = num of strings in words that start with "a"
        // prefix "ab", #count2 = num of strings in words that start with "ab"
        // prefix "abc", #count3 = num of strings in words that start with "abc"
        // score of s = #count1 + #count2 + #count3
        Trie trie;
        for (const auto& s : words) {
            trie.insert(s);
        }
        std::vector<int> result;
        result.reserve(words.size());
        for (const auto& s : words) {
            result.push_back(trie.score(s));
        }
        return result;
    }
};