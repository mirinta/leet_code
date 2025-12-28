#include <array>
#include <string>
#include <vector>

/**
 * You are given a string word and an array of strings forbidden.
 *
 * A string is called valid if none of its substrings are present in forbidden.
 *
 * Return the length of the longest valid substring of the string word.
 *
 * A substring is a contiguous sequence of characters in a string, possibly empty.
 *
 * ! 1 <= word.length <= 10^5
 * ! word consists only of lowercase English letters.
 * ! 1 <= forbidden.length <= 10^5
 * ! 1 <= forbidden[i].length <= 10
 * ! forbidden[i] consists only of lowercase English letters.
 */

class Trie {
public:
    explicit Trie() : root(new TrieNode()) {}

    void insertReversely(const std::string& s)
    {
        auto* node = root;
        for (auto iter = s.rbegin(); iter != s.rend(); ++iter) {
            const int index = *iter - 'a';
            if (!node->next[index]) {
                node->next[index] = new TrieNode();
            }
            node = node->next[index];
        }
        node->isEnd = true;
    }

    bool contains(int lo, int hi, const std::string& s)
    {
        auto* node = root;
        for (int i = hi; i >= lo; --i) {
            const int index = s[i] - 'a';
            if (!node->next[index])
                return false;

            node = node->next[index];
            if (node->isEnd)
                return true;
        }
        return node->isEnd;
    }

private:
    struct TrieNode {
        std::array<TrieNode*, 26> next;
        bool isEnd{false};
    };

    TrieNode* root;
};

class Solution {
public:
    int longestValidSubstring(std::string word, std::vector<std::string>& forbidden)
    {
        // given L, move R from left to right
        // if all suffix subarrays of word[L:R] are not in the "forbidden",
        // then all subarrays of word[L:R] ending at word[R] are valid,
        // num of those subarrays = R-L+1
        const int n = word.size();
        Trie trie;
        for (const auto& s : forbidden) {
            trie.insertReversely(s);
        }
        int result = 0;
        for (int left = 0, right = 0; right < n; ++right) {
            while (trie.contains(left, right, word)) {
                left++;
            }
            result = std::max(result, right - left + 1);
        }
        return result;
    }
};