#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

/**
 * Design a search autocomplete system for a search engine. Users may input a sentence (at least one
 * word and end with a special character '#').
 *
 * You are given a string array sentences and an integer array times both of length n where
 * sentences[i] is a previously typed sentence and times[i] is the corresponding number of times the
 * sentence was typed. For each input character except '#', return the top 3 historical hot
 * sentences that have the same prefix as the part of the sentence already typed.
 *
 * Here are the specific rules:
 *
 * - The hot degree for a sentence is defined as the number of times a user typed the exactly same
 * sentence before.
 *
 * - The returned top 3 hot sentences should be sorted by hot degree (The first is the hottest one).
 * If several sentences have the same hot degree, use ASCII-code order (smaller one appears first).
 *
 * - If less than 3 hot sentences exist, return as many as you can.
 *
 * - When the input is a special character, it means the sentence ends, and in this case, you need
 * to return an empty list.
 *
 * Implement the AutocompleteSystem class:
 *
 * - AutocompleteSystem(String[] sentences, int[] times) Initializes the object with the sentences
 * and times arrays.
 *
 * - List<String> input(char c) This indicates that the user typed the character c.
 *
 * -- Returns an empty array [] if c == '#' and stores the inputted sentence in the system.
 *
 * -- Returns the top 3 historical hot sentences that have the same prefix as the part of the
 * sentence already typed. If there are fewer than 3 matches, return them all.
 *
 * ! n == sentences.length
 * ! n == times.length
 * ! 1 <= n <= 100
 * ! 1 <= sentences[i].length <= 100
 * ! 1 <= times[i] <= 50
 * ! c is a lowercase English letter, a hash '#', or space ' '.
 * ! Each tested sentence will be a sequence of characters c that end with the character '#'.
 * ! Each tested sentence will have a length in the range [1, 200].
 * ! The words in each input sentence are separated by single spaces.
 * ! At most 5000 calls will be made to input.
 */

struct TrieNode {
    int times{0};
    std::unordered_map<char, TrieNode*> next;
};

class Trie {
public:
    explicit Trie() : root(new TrieNode()) {};

    void insert(const std::string& sentence, int times = 1)
    {
        auto* node = root;
        for (const auto& c : sentence) {
            if (!node->next.count(c)) {
                node->next[c] = new TrieNode();
            }
            node = node->next[c];
        }
        node->times += times;
    }

    std::vector<std::string> top3HotSentences(const std::string& prefix)
    {
        std::string sentence;
        auto* node = root;
        for (const auto& c : prefix) {
            if (!node->next.count(c))
                return {};

            sentence.push_back(c);
            node = node->next[c];
        }
        backtrack(sentence, node);
        std::vector<std::string> result(pq.size());
        for (int i = result.size() - 1; i >= 0; --i) {
            result[i] = pq.top().first;
            pq.pop();
        }
        return result;
    }

private:
    void backtrack(std::string& sentence, TrieNode* node)
    {
        if (node->times > 0) {
            pq.emplace(sentence, node->times);
            if (pq.size() > 3) {
                pq.pop();
            }
        }
        for (const auto& [c, child] : node->next) {
            sentence.push_back(c);
            backtrack(sentence, child);
            sentence.pop_back();
        }
    }

private:
    TrieNode* root;

    using Pair = std::pair<std::string, int>; // <sentence, times>
    struct Compare {
        bool operator()(const Pair& p1, const Pair& p2)
        {
            return p1.second == p2.second ? p1.first < p2.first : p1.second > p2.second;
            ;
        }
    };
    using PQ = std::priority_queue<Pair, std::vector<Pair>, Compare>;
    PQ pq;
};

class AutocompleteSystem {
public:
    AutocompleteSystem(std::vector<std::string>& sentences, std::vector<int>& times)
    {
        for (int i = 0; i < sentences.size(); ++i) {
            trie.insert(sentences[i], times[i]);
        }
    }

    std::vector<std::string> input(char c)
    {
        if (c == '#') {
            trie.insert(prefix);
            prefix.clear();
            return {};
        }
        prefix.push_back(c);
        return trie.top3HotSentences(prefix);
    }

private:
    Trie trie;
    std::string prefix;
};

/**
 * Your AutocompleteSystem object will be instantiated and called as such:
 * AutocompleteSystem* obj = new AutocompleteSystem(sentences, times);
 * vector<string> param_1 = obj->input(c);
 */