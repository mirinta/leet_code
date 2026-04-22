#include <array>
#include <string>
#include <vector>

/**
 * You are given two string arrays, queries and dictionary. All words in each array comprise of lowercase English
 * letters and have the same length.
 *
 * In one edit you can take a word from queries, and change any letter in it to any other letter. Find all words from
 * queries that, after a maximum of two edits, equal some word from dictionary.
 *
 * Return a list of all words from queries, that match with some word from dictionary after a maximum of two edits.
 * Return the words in the same order they appear in queries.
 *
 * ! 1 <= queries.length, dictionary.length <= 100
 * ! n == queries[i].length == dictionary[j].length
 * ! 1 <= n <= 100
 * ! All queries[i] and dictionary[j] are composed of lowercase English letters.
 */

class Trie {
    struct TrieNode {
        std::array<TrieNode*, 26> next{};
        bool end{false};
    };

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
        }
        node->end = true;
    }

    bool isValid(const std::string& s)
    {
        return dfs(root, 0, 0, s);
    }

private:
    bool dfs(TrieNode* node, int count, int i, const std::string& s)
    {
        if (!node || count > 2)
            return false;

        if (i == s.size())
            return node->end;

        const int index = s[i] - 'a';
        if (dfs(node->next[index], count, i + 1, s))
            return true;

        if (count == 2)
            return false;

        for (int k = 0; k < 26; ++k) {
            if (k != index && dfs(node->next[k], count + 1, i + 1, s))
                return true;
        }
        return false;
    }

private:
    TrieNode* root;
};

class Solution {
public:
    std::vector<std::string> twoEditWords(std::vector<std::string>& queries, std::vector<std::string>& dictionary)
    {
        Trie trie;
        for (const auto& s : dictionary) {
            trie.insert(s);
        }
        std::vector<std::string> result;
        for (const auto& q : queries) {
            if (trie.isValid(q)) {
                result.push_back(q);
            }
        }
        return result;
    }
};
