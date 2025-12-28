#include <array>
#include <memory>
#include <string>
#include <vector>

/**
 * Design a map that allows you to do the following:
 *
 * - Maps a string key to a given value.
 *
 * - Returns the sum of the values that have a key with a prefix equal to a given string.
 *
 * Implement the MapSum class:
 *
 * - MapSum() Initializes the MapSum object.
 *
 * - void insert(String key, int val) Inserts the key-val pair into the map. If the key already
 * existed, the original key-value pair will be overridden to the new one.
 *
 * - int sum(string prefix) Returns the sum of all the pairs' value whose key starts with the
 * prefix.
 */

struct TrieNode {
    static constexpr int R = 26;
    std::array<std::unique_ptr<TrieNode>, 26> next;
    int value = 0;
};

class MapSum {
public:
    MapSum() : root(std::make_unique<TrieNode>()) {}

    void insert(const std::string& key, int val)
    {
        auto* node = root.get();
        for (const auto& c : key) {
            const int index = c - 'a';
            if (!node->next[index]) {
                node->next[index] = std::make_unique<TrieNode>();
            }
            node = node->next[index].get();
        }
        node->value = val;
    }

    int sum(const std::string& prefix)
    {
        auto* node = root.get();
        for (const auto& c : prefix) {
            const int index = c - 'a';
            if (!node->next[index])
                return 0;

            node = node->next[index].get();
        }
        return dfs(node);
    }

private:
    int dfs(TrieNode* node)
    {
        if (!node)
            return 0;

        int result = 0;
        for (const auto& ptr : node->next) {
            result += dfs(ptr.get());
        }
        return node->value + result;
    }

private:
    std::unique_ptr<TrieNode> root;
};

/**
 * Your MapSum object will be instantiated and called as such:
 * MapSum* obj = new MapSum();
 * obj->insert(key,val);
 * int param_2 = obj->sum(prefix);
 */
