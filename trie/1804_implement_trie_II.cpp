#include <algorithm>
#include <string>
#include <unordered_map>

struct TrieNode {
    std::unordered_map<char, TrieNode*> next{};
    int countPass = 0; // num of words passing this node
    int countWord = 0; // num of words ending at this node

    ~TrieNode()
    {
        auto iter = next.begin();
        while (iter != next.end()) {
            delete iter->second;
            ++iter;
        }
    }
};

class Trie {
public:
    Trie() : root(new TrieNode()) {}

    ~Trie()
    {
        delete root;
    }

    void insert(const std::string& word)
    {
        auto* node = root;
        for (const auto& c : word) {
            if (!node->next.count(c)) {
                node->next[c] = new TrieNode();
            }
            node->next[c]->countPass++;
            node = node->next[c];
        }
        node->countWord++;
    }

    int countWordsEqualTo(const std::string& word)
    {
        auto* node = root;
        for (const auto& c : word) {
            if (!node->next.count(c))
                return 0;

            node = node->next[c];
        }
        return node->countWord;
    }

    int countWordsStartingWith(const std::string& prefix)
    {
        auto* node = root;
        for (const auto& c : prefix) {
            if (!node->next.count(c))
                return 0;

            node = node->next[c];
        }
        return node->countPass;
    }

    void erase(const std::string& word)
    {
        // it is guaranteed that the given word exists in the trie
        auto* node = root;
        for (const auto& c : word) {
            if (!node->next.count(c))
                return;

            if (--node->next[c]->countPass == 0) {
                node->next.erase(c);
                return;
            }
            node = node->next[c];
        }
        --node->countWord;
    }

private:
    TrieNode* root;
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * int param_2 = obj->countWordsEqualTo(word);
 * int param_3 = obj->countWordsStartingWith(prefix);
 * obj->erase(word);
 */