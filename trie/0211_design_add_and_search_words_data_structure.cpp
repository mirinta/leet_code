#include <functional>
#include <string>
#include <unordered_map>

/**
 * Design a data structure that supports adding new words and finding if a string matches any
 * previously added string.
 *
 * Implement the WordDictionary class:
 *
 * - WordDictionary() Initializes the object.
 *
 * - void addWord(word) Adds word to the data structure, it can be matched later.
 *
 * - bool search(word) Returns true if there is any string in the data structure that matches word
 * or false otherwise. word may contain dots '.' where dots can be matched with any letter.
 *
 * ! 1 <= word.length <= 25
 * ! word in addWord consists of lowercase English letters.
 * ! word in search consist of '.' or lowercase English letters.
 * ! There will be at most 2 dots in word for search queries.
 * ! At most 10^4 calls will be made to addWord and search.
 */

class Trie {
    struct TrieNode {
        std::unordered_map<char, TrieNode*> next;
        bool isEnd{false};
    };

public:
    explicit Trie() : root(new TrieNode()) {}

    void insert(const std::string& word)
    {
        auto* node = root;
        for (const auto& c : word) {
            if (!node->next.count(c)) {
                node->next[c] = new TrieNode();
            }
            node = node->next[c];
        }
        node->isEnd = true;
    }

    bool fuzzySearch(const std::string& word)
    {
        const int n = word.size();
        std::vector<std::string> result;
        std::function<bool(int, TrieNode*)> dfs = [&](int i, TrieNode* node) {
            if (i == n)
                return node->isEnd;

            if (word[i] != '.')
                return node->next.count(word[i]) && dfs(i + 1, node->next[word[i]]);

            for (const auto& [c, child] : node->next) {
                if (dfs(i + 1, child))
                    return true;
            }
            return false;
        };
        return dfs(0, root);
    }

private:
    TrieNode* root;
};

class WordDictionary {
public:
    WordDictionary() {}

    void addWord(const std::string& word)
    {
        trie.insert(word);
    }

    bool search(const std::string& word)
    {
        return trie.fuzzySearch(word);
    }

private:
    Trie trie;
};

/**
 * Your WordDictionary object will be instantiated and called as such:
 * WordDictionary* obj = new WordDictionary();
 * obj->addWord(word);
 * bool param_2 = obj->search(word);
 */