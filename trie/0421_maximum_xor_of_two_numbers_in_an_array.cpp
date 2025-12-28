#include <algorithm>
#include <string>
#include <vector>

/**
 * Given an integer array nums, return the maximum result of nums[i] XOR nums[j], where 0 <= i <= j
 * < n.
 *
 *
 * ! 1 <= nums.length <= 2 * 10^5
 * ! 0 <= nums[i] <= 2^31 - 1
 */

struct TrieNode {
    TrieNode* next[2];
};

class Solution {
public:
    int findMaximumXOR(std::vector<int>& nums)
    {
        const int bits = numOfBits(*std::max_element(nums.begin(), nums.end()));
        std::vector<std::string> strs;
        auto* root = new TrieNode();
        for (auto val : nums) {
            std::string s;
            auto* node = root;
            for (int i = bits; i >= 0; --i) {
                const int bitVal = (val >> i) & 1;
                s.push_back(bitVal + '0');
                if (!node->next[bitVal]) {
                    node->next[bitVal] = new TrieNode();
                }
                node = node->next[bitVal];
            }
            strs.push_back(std::move(s));
        }
        int result = 0;
        for (const auto& s : strs) {
            auto* node = root;
            int val = 0;
            for (const auto& c : s) {
                const int bitVal = c - '0';
                if (node->next[1 - bitVal]) {
                    val = val * 2 + 1;
                    node = node->next[1 - bitVal];
                } else {
                    val = val * 2;
                    node = node->next[bitVal];
                }
            }
            result = std::max(result, val);
        }
        return result;
    }

private:
    int numOfBits(int val)
    {
        int count = 0;
        while (val) {
            count++;
            val >>= 1;
        }
        return count;
    }
};