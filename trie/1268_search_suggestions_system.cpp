#include <array>
#include <memory>
#include <string>
#include <vector>

/**
 * You are given an array of strings products and a string searchWord.
 *
 * Design a system that suggests at most three product names from products after each character of
 * searchWord is typed. Suggested products should have common prefix with searchWord. If there are
 * more than three products with a common prefix return the three lexicographically minimums
 * products.
 *
 * Return a list of lists of the suggested products after each character of searchWord is typed.
 *
 * ! 1 <= products.length <= 1000
 * ! 1 <= products[i].length <= 3000
 * ! 1 <= sum(products[i].length) <= 2 * 10^4
 * ! All the strings of products are unique.
 * ! products[i] consists of lowercase English letters.
 * ! 1 <= searchWord.length <= 1000
 * ! searchWord consists of lowercase English letters.
 */

struct TrieNode {
    static constexpr int R = 26;
    bool isEnd = false;
    std::array<std::unique_ptr<TrieNode>, R> next;
};

class Trie {
public:
    explicit Trie() : root(std::make_unique<TrieNode>()) {}

    void insert(const std::string& word)
    {
        auto* node = root.get();
        for (const auto& c : word) {
            const int index = c - 'a';
            if (!node->next[index]) {
                node->next[index] = std::make_unique<TrieNode>();
            }
            node = node->next[index].get();
        }
        node->isEnd = true;
    }

    std::vector<std::string> getWordsWithPrefix(const std::string& prefix, int numLimit)
    {
        std::vector<std::string> result;
        auto* node = root.get();
        for (const auto& c : prefix) {
            const int index = c - 'a';
            if (!node->next[index])
                return result;

            node = node->next[index].get();
        }
        std::string word(prefix);
        dfsWithPrefix(result, word, node, numLimit);
        return result;
    }

private:
    void dfsWithPrefix(std::vector<std::string>& result, std::string& word, TrieNode* node, int numLimit)
    {
        if (!node || result.size() == numLimit)
            return;

        if (node->isEnd) {
            result.push_back(word);
        }
        for (int i = 0; i < node->next.size(); ++i) {
            if (!node->next[i])
                continue;

            word.push_back(i + 'a');
            dfsWithPrefix(result, word, node->next[i].get(), numLimit);
            word.pop_back();
        }
    }

private:
    std::unique_ptr<TrieNode> root;
};

class Solution {
public:
    std::vector<std::vector<std::string>> suggestedProducts(const std::vector<std::string>& products,
                                                            const std::string& searchWord)
    {
        Trie trie;
        for (const auto& name : products) {
            trie.insert(name);
        }
        std::vector<std::vector<std::string>> result;
        std::string prefix;
        for (const auto& c : searchWord) {
            prefix.push_back(c);
            result.push_back(trie.getWordsWithPrefix(prefix, 3));
        }
        return result;
    }
};
