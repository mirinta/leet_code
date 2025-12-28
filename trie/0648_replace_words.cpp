#include <array>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

/**
 * In English, we have a concept called root, which can be followed by some other word to form
 * another longer word - let's call this word successor. For example, when the root "an" is followed
 * by the successor word "other", we can form a new word "another".
 *
 * Given a dictionary consisting of many roots and a sentence consisting of words separated by
 * spaces, replace all the successors in the sentence with the root forming it. If a successor can
 * be replaced by more than one root, replace it with the root that has the shortest length.
 *
 * Return the sentence after the replacement.
 *
 * ! 1 <= dictionary.length <= 1000
 * ! 1 <= dictionary[i].length <= 100
 * ! dictionary[i] consists of only lower-case letters.
 * ! 1 <= sentence.length <= 10^6
 * ! sentence consists of only lower-case letters and spaces.
 * ! The number of words in sentence is in the range [1, 1000]
 * ! The length of each word in sentence is in the range [1, 1000]
 * ! Every two consecutive words in sentence will be separated by exactly one space.
 * ! sentence does not have leading or trailing spaces.
 */

class Trie {
public:
    explicit Trie() : root(new TrieNode()) {}

    void insert(const std::string& s)
    {
        auto* node = root;
        for (const auto& c : s) {
            const int index = c - 'a';
            if (!node->next[index]) {
                node->next[index] = new TrieNode();
            }
            node = node->next[index];
        }
        node->isEnd = true;
    }

    std::string shortestPrefix(const std::string& s)
    {
        auto* node = root;
        std::string result;
        for (const auto& c : s) {
            const int index = c - 'a';
            if (!node->next[index])
                return {};

            result.push_back(c);
            node = node->next[index];
            if (node->isEnd)
                break;
        }
        return result;
    }

private:
    struct TrieNode {
        std::array<TrieNode*, 26> next{};
        bool isEnd{false};
    };

    TrieNode* root;
};

class Solution {
public:
    std::string replaceWords(std::vector<std::string>& dictionary, std::string sentence)
    {
        Trie trie;
        for (const auto& s : dictionary) {
            trie.insert(s);
        }
        const int n = sentence.size();
        std::string result;
        for (int i = 0, last = -1; i <= n; ++i) {
            if (i < n && sentence[i] != ' ')
                continue;

            const auto sub = sentence.substr(last + 1, i - last - 1);
            const auto prefix = trie.shortestPrefix(sub);
            result.append(prefix.empty() ? sub : prefix);
            result.push_back(' ');
            last = i;
        }
        result.pop_back();
        return result;
    }
};