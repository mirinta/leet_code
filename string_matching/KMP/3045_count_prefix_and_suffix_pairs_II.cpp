#include <array>
#include <string>
#include <unordered_set>
#include <vector>

/**
 * You are given a 0-indexed string array words.
 *
 * Let's define a boolean function isPrefixAndSuffix that takes two strings, str1 and str2:
 *
 * - isPrefixAndSuffix(str1, str2) returns true if str1 is both a prefix and a suffix of str2, and
 * false otherwise.
 *
 * For example, isPrefixAndSuffix("aba", "ababa") is true because "aba" is a prefix of "ababa" and
 * also a suffix, but isPrefixAndSuffix("abc", "abcd") is false.
 *
 * Return an integer denoting the number of index pairs (i, j) such that i < j, and
 * isPrefixAndSuffix(words[i], words[j]) is true.
 *
 * ! 1 <= words.length <= 10^5
 * ! 1 <= words[i].length <= 10^5
 * ! words[i] consists only of lowercase English letters.
 * ! The sum of the lengths of all words[i] does not exceed 5 * 10^5.
 */

class Trie {
public:
    explicit Trie() : root(new TrieNode()) {}

    void insert(const std::string& word)
    {
        auto* node = root;
        for (const auto& c : word) {
            const int index = c - 'a';
            if (!node->next[index]) {
                node->next[index] = new TrieNode();
            }
            node = node->next[index];
        }
        node->count++;
    }

    int count(const std::string& word, const std::unordered_set<int>& set = {})
    {
        auto* node = root;
        int result = 0;
        for (int i = 0; i < word.size(); ++i) {
            const int index = word[i] - 'a';
            if (!node->next[index])
                break;

            node = node->next[index];
            if (set.count(i + 1)) {
                result += node->count;
            }
        }
        return result;
    }

private:
    struct TrieNode {
        std::array<TrieNode*, 26> next;
        int count{0};
    };

    TrieNode* root;
};

class Solution {
public:
    long long countPrefixSuffixPairs(std::vector<std::string>& words)
    {
        Trie trie;
        long long result = 0;
        for (const auto& word : words) {
            const auto next = helper(word);
            const int n = word.size();
            std::unordered_set<int> set;
            for (int L = n; L > 0; L = next[L - 1]) {
                set.insert(L);
            }
            result += trie.count(word, set);
            trie.insert(word);
        }
        return result;
    }

private:
    std::vector<int> helper(const std::string& s)
    {
        const int n = s.size();
        std::vector<int> next(n);
        next[0] = 0;
        for (int i = 1; i < n; ++i) {
            int L = next[i - 1];
            while (L >= 1 && s[L] != s[i]) {
                L = next[L - 1];
            }
            next[i] = L + (s[L] == s[i]);
        }
        return next;
    }
};