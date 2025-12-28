#include <array>
#include <string>
#include <vector>

/**
 * You are given two arrays of strings wordsContainer and wordsQuery.
 *
 * For each wordsQuery[i], you need to find a string from wordsContainer that has the longest common
 * suffix with wordsQuery[i]. If there are two or more strings in wordsContainer that share the
 * longest common suffix, find the string that is the smallest in length. If there are two or more
 * such strings that have the same smallest length, find the one that occurred earlier in
 * wordsContainer.
 *
 * Return an array of integers ans, where ans[i] is the index of the string in wordsContainer that
 * has the longest common suffix with wordsQuery[i].
 *
 * ! 1 <= wordsContainer.length, wordsQuery.length <= 10^4
 * ! 1 <= wordsContainer[i].length <= 5 * 10^3
 * ! 1 <= wordsQuery[i].length <= 5 * 10^3
 * ! wordsContainer[i] consists only of lowercase English letters.
 * ! wordsQuery[i] consists only of lowercase English letters.
 * ! Sum of wordsContainer[i].length is at most 5 * 10^5.
 * ! Sum of wordsQuery[i].length is at most 5 * 10^5.
 */

class Trie {
public:
    explicit Trie() : root(new TrieNode()) {}

    void insert(const std::string& s, int index)
    {
        const int length = s.size();
        auto* node = root;
        for (auto iter = s.rbegin(); iter != s.rend(); ++iter) {
            const int i = *iter - 'a';
            if (!node->next[i]) {
                node->next[i] = new TrieNode();
            }
            node = node->next[i];
            if (length < node->length) {
                node->length = length;
                node->index = index;
            }
        }
    }

    int find(const std::string& suffix)
    {
        auto* node = root;
        for (auto iter = suffix.rbegin(); iter != suffix.rend(); ++iter) {
            const int i = *iter - 'a';
            if (!node->next[i])
                break;

            node = node->next[i];
        }
        return node->index;
    }

private:
    struct TrieNode {
        std::array<TrieNode*, 26> next;
        int index{-1};
        int length{INT_MAX};
    };

    TrieNode* root;
};

class Solution {
public:
    std::vector<int> stringIndices(std::vector<std::string>& wordsContainer, std::vector<std::string>& wordsQuery)
    {
        Trie trie;
        int minLength = INT_MAX;
        int minIndex = INT_MAX;
        for (int i = 0; i < wordsContainer.size(); ++i) {
            trie.insert(wordsContainer[i], i);
            if (wordsContainer[i].size() < minLength) {
                minLength = wordsContainer[i].size();
                minIndex = i;
            }
        }
        std::vector<int> result(wordsQuery.size());
        for (int i = 0; i < wordsQuery.size(); ++i) {
            const int j = trie.find(wordsQuery[i]);
            result[i] = j == -1 ? minIndex : j;
        }
        return result;
    }
};