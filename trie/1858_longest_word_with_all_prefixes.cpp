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
    struct TrieNode {
        std::array<std::unique_ptr<TrieNode>, 26> next{};
        bool isEnd{false};
    };

public:
    explicit Trie() : root(new TrieNode) {}

    void insert(const std::string& s)
    {
        auto* node = root.get();
        for (const auto& c : s) {
            const int index = c - 'a';
            if (!node->next[index]) {
                node->next[index] = std::make_unique<TrieNode>();
            }
            node = node->next[index].get();
        }
        node->isEnd = true;
    }

    bool isValid(const std::string& s)
    {
        auto* node = root.get();
        for (const auto& c : s) {
            const int index = c - 'a';
            if (!node->next[index])
                return false;

            node = node->next[index].get();
            if (!node->isEnd)
                return false;
        }
        return true;
    }

private:
    std::unique_ptr<TrieNode> root;
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
            if (!trie.isValid(s) || s.size() < result.size())
                continue;

            result = s.size() > result.size() ? s : std::min(result, s);
        }
        return result;
    }
};