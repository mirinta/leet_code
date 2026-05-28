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
    struct TrieNode {
        std::array<TrieNode*, 26> next{};
        int length{INT_MAX};
        int index{INT_MAX};

        ~TrieNode()
        {
            for (int i = 0; i < 26; ++i) {
                delete next[i];
            }
        }
    };

public:
    explicit Trie() : root(new TrieNode) {}

    ~Trie()
    {
        delete root;
    }

    void insertReversely(const std::string& s, int index)
    {
        const int n = s.size();
        auto* node = root;
        for (int i = n - 1; i >= 0; --i) {
            if (!node->next[s[i] - 'a']) {
                node->next[s[i] - 'a'] = new TrieNode;
            }
            node = node->next[s[i] - 'a'];
            if (n < node->length) {
                node->length = n;
                node->index = index;
            } else if (n == node->length && index < node->index) {
                node->index = index;
            }
        }
    }

    int findReversely(const std::string& s)
    {
        const int n = s.size();
        auto* node = root;
        for (int i = n - 1; i >= 0; --i) {
            if (!node->next[s[i] - 'a'])
                break;

            node = node->next[s[i] - 'a'];
        }
        return node->index;
    }

private:
    TrieNode* root;
};

class Solution {
public:
    std::vector<int> stringIndices(std::vector<std::string>& wordsContainer, std::vector<std::string>& wordsQuery)
    {
        Trie trie;
        const int n = wordsContainer.size();
        int shortestLength = INT_MAX;
        int shortest = -1;
        for (int i = 0; i < n; ++i) {
            trie.insertReversely(wordsContainer[i], i);
            if (wordsContainer[i].size() < shortestLength) {
                shortestLength = wordsContainer[i].size();
                shortest = i;
            }
        }
        std::vector<int> result;
        result.reserve(wordsQuery.size());
        for (const auto& s : wordsQuery) {
            const int j = trie.findReversely(s);
            result.push_back(j == INT_MAX ? shortest : j);
        }
        return result;
    }
};
