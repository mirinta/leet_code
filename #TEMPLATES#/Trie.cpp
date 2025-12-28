#include <functional>
#include <string>
#include <unordered_map>

class Trie {
    struct TrieNode {
        bool isEnd{false};
        std::unordered_map<char, TrieNode*> next;
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

    bool exactSearch(const std::string& word)
    {
        auto* node = root;
        for (const auto& c : word) {
            if (!node->next.count(c))
                return false;

            node = node->next[c];
        }
        return node->isEnd;
    }

    /**
     * @param word may contains dots '.' where dots can be matched with any character.
     */
    std::vector<std::string> fuzzySearch(const std::string& word)
    {
        const int n = word.size();
        std::string s;
        std::vector<std::string> result;
        std::function<void(int, TrieNode*)> dfs = [&](int i, TrieNode* node) {
            if (i == n) {
                if (node->isEnd) {
                    result.push_back(s);
                }
                return;
            }
            if (word[i] != '.') {
                if (!node->next.count(word[i]))
                    return;

                s.push_back(word[i]);
                dfs(i + 1, node->next[word[i]]);
                s.pop_back();
                return;
            }
            for (const auto& [c, child] : node->next) {
                s.push_back(c);
                dfs(i + 1, child);
                s.pop_back();
            }
        };
        dfs(0, root);
        return result;
    }

    std::string longestCommonPrefix()
    {
        std::string result;
        auto* node = root;
        while (true) {
            if (node->next.size() != 1 || node->isEnd)
                break;

            result.push_back(node->next.begin()->first);
            node = node->next.begin()->second;
        }
        return result;
    }

private:
    TrieNode* root;
};