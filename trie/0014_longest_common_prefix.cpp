#include <string>
#include <unordered_map>
#include <vector>

/**
 * Write a function to find the longest common prefix string amongst an array of strings.
 *
 * If there is no common prefix, return an empty string "".
 *
 * ! 1 <= strs.length <= 200
 * ! 0 <= strs[i].length <= 200
 * ! strs[i] consists of only lowercase English letters.
 */

struct TrieNode {
    bool isEnd = false;
    std::unordered_map<char, TrieNode*> next;
};

class Trie {
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

class Solution {
public:
    std::string longestCommonPrefix(std::vector<std::string>& strs)
    {
        return approach2(strs);
    }

private:
    std::string approach2(const std::vector<std::string>& strs)
    {
        // search length of the common prefix
        int lo = 0;
        int hi = INT_MAX;
        for (const auto& word : strs) {
            hi = std::min<int>(hi, word.size());
        }
        while (lo < hi) {
            const int mid = hi - (hi - lo) / 2;
            if (isValid(mid, strs)) {
                lo = mid;
            } else {
                hi = mid - 1;
            }
        }
        return strs[0].substr(0, lo);
    }

    bool isValid(int prefixLength, const std::vector<std::string>& strs)
    {
        const std::string prefix = strs[0].substr(0, prefixLength);
        for (const auto& str : strs) {
            for (int j = 0; j < prefixLength; ++j) {
                if (str[j] != prefix[j])
                    return false;
            }
        }
        return true;
    }

    // Trie
    std::string approach1(const std::vector<std::string>& strs)
    {
        Trie trie;
        for (const auto& word : strs) {
            if (word.empty())
                return {};

            trie.insert(word);
        }
        return trie.longestCommonPrefix();
    }
};
