#include <array>
#include <string>
#include <vector>

/**
 * Given an array of strings words, find the longest string in words such that every prefix of it is
 * also in words.
 *
 * - For example, let words = ["a", "app", "ap"]. The string "app" has prefixes "ap" and "a", all of
 * which are in words.
 *
 * Return the string described above. If there is more than one string with the same length, return
 * the lexicographically smallest one, and if no string exists, return "".
 *
 *
 * ! 1 <= words.length <= 10^5
 * ! 1 <= words[i].length <= 10^5
 * ! 1 <= sum(words[i].length) <= 10^5
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
        }
        node->isEnd = true;
    }

    // check if every prefix of s is in the trie
    bool check(const std::string& s)
    {
        auto* node = root;
        for (const auto& c : s) {
            const int index = c - 'a';
            if (!node->next[index])
                return false;

            node = node->next[index];
            if (!node->isEnd)
                return false;
        }
        return true;
    }

private:
    struct TrieNode {
        bool isEnd{false};
        std::array<TrieNode*, 26> next{};
    };

    TrieNode* root;
};

class Solution {
public:
    std::string longestWord(std::vector<std::string>& words)
    {
        Trie trie;
        for (const auto& s : words) {
            trie.insert(s);
        }
        std::string result;
        for (const auto& s : words) {
            if (!trie.check(s) || s.size() < result.size())
                continue;

            result = s.size() > result.size() ? s : std::min(result, s);
        }
        return result;
    }
};