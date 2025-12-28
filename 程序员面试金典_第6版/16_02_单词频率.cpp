#include <array>
#include <string>
#include <vector>

/**
 * 设计一个方法，找出任意指定单词在一本书中的出现频率。
 *
 * 你的实现应该支持如下操作：
 *
 * WordsFrequency(book)构造函数，参数为字符串数组构成的一本书
 * get(word)查询指定单词在书中出现的频率
 *
 * ! book[i]中只包含小写字母
 * ! 1 <= book.length <= 100000
 * ! 1 <= book[i].length <= 10
 * ! get函数的调用次数不会超过100000
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
        node->count++;
    }

    int count(const std::string& s)
    {
        auto* node = root;
        for (const auto& c : s) {
            const int index = c - 'a';
            if (!node->next[index])
                return 0;

            node = node->next[index];
        }
        return node->count;
    }

private:
    struct TrieNode {
        std::array<TrieNode*, 26> next;
        int count{0};
    };

    TrieNode* root;
};

class WordsFrequency {
public:
    WordsFrequency(std::vector<std::string>& book)
    {
        for (const auto& s : book) {
            trie.insert(s);
        }
    }

    int get(const std::string& word)
    {
        return trie.count(word);
    }

private:
    Trie trie;
};

/**
 * Your WordsFrequency object will be instantiated and called as such:
 * WordsFrequency* obj = new WordsFrequency(book);
 * int param_1 = obj->get(word);
 */