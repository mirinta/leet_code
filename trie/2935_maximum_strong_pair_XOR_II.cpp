#include <algorithm>
#include <array>
#include <vector>

/**
 * You are given a 0-indexed integer array nums. A pair of integers x and y is called a strong pair
 * if it satisfies the condition:
 *
 * - |x - y| <= min(x, y)
 *
 * You need to select two integers from nums such that they form a strong pair and their bitwise XOR
 * is the maximum among all strong pairs in the array.
 *
 * Return the maximum XOR value out of all possible strong pairs in the array nums.
 *
 * Note that you can pick the same integer twice to form a pair.
 *
 * ! 1 <= nums.length <= 5 * 10^4
 * ! 1 <= nums[i] <= 2^20 - 1
 */

struct TrieNode {
    int count = 0;
    std::array<TrieNode*, 2> next{nullptr, nullptr};
};

class Trie {
public:
    Trie() : root(new TrieNode()) {}

    void insert(int val)
    {
        auto* node = root;
        for (int i = 31; i >= 0; --i) {
            const int bit = (val >> i) & 1;
            if (!node->next[bit]) {
                node->next[bit] = new TrieNode();
            }
            node->next[bit]->count++;
            node = node->next[bit];
        }
    }

    void remove(int val)
    {
        auto* node = root;
        for (int i = 31; i >= 0; --i) {
            const int bit = (val >> i) & 1;
            if (!node->next[bit])
                return;

            if (--node->next[bit]->count == 0) {
                delete node->next[bit];
                node->next[bit] = nullptr;
                return;
            }
            node = node->next[bit];
        }
    }

    int maxXOR(int val)
    {
        int result = 0;
        auto* node = root;
        for (int i = 31; i >= 0; --i) {
            const int bit = (val >> i) & 1;
            if (node->next[1 - bit]) {
                result |= (1 << i);
                node = node->next[1 - bit];
                continue;
            }
            node = node->next[bit];
        }
        return result;
    }

private:
    TrieNode* root;
};

class Solution {
public:
    int maximumStrongPairXor(std::vector<int>& nums)
    {
        // |x - y| <= min(x, y)
        // assume x <= y,
        // then y - x <= x which means 2x >= y
        std::sort(nums.begin(), nums.end());
        int result = INT_MIN;
        Trie trie;
        for (int i = 0, j = 0; i < nums.size(); ++i) {
            trie.insert(nums[i]);
            while (nums[j] * 2 < nums[i]) {
                trie.remove(nums[j++]);
            }
            result = std::max(result, trie.maxXOR(nums[i]));
        }
        return result;
    }
};