#include <array>
#include <string>
#include <unordered_set>
#include <vector>

/**
 * Given a string "s" and a dictionary of strings "wordDict", return true if "s" can be segmented
 * into a space-separated sequence of one or more dictionary words.
 *
 * Note that the same word in the dictionary may be used multiple times in the segmentation.
 *
 * ! 1 <= s.length <= 300
 * ! 1 <= wordDict.length <= 1000
 * ! 1 <= wordDict[i].length <= 20
 * ! s and wordDict[i] consist of only lowercase English letters.
 * ! All the strings of wordDict are unique.
 */

struct TrieNode {
    static constexpr int R = 26;
    std::array<TrieNode*, R> next{};
    bool isEnd = false;

    ~TrieNode()
    {
        auto iter = next.begin();
        while (iter != next.end()) {
            delete *iter;
            iter++;
        }
    };
};

class Solution {
public:
    bool wordBreak(std::string s, std::vector<std::string>& wordDict)
    {
        return approach2(s, wordDict);
    }

private:
    // DP + Trie
    bool approach2(const std::string& s, const std::vector<std::string>& wordDict)
    {
        TrieNode root;
        for (const auto& word : wordDict) {
            auto* node = &root;
            for (const auto& c : word) {
                const int index = c - 'a';
                if (!node->next[index]) {
                    node->next[index] = new TrieNode;
                }
                node = node->next[index];
            }
            node->isEnd = true;
        }
        const int n = s.size();
        std::vector<bool> dp(n, false); // dp[i] = whether s[0:i] can be segmented
        // 0 X X X X i-1 i X X X X j ... n-1
        // |<-dp[i-1]->| |<--word->|
        // |<--------dp[j]-------->|
        // if s[0:j] can be segmented, then s[0:i-1] can be segmented and s[i:j] is in the
        // dictionary
        for (int i = 0; i < n; ++i) {
            if (i == 0 || dp[i - 1]) {
                auto* node = &root;
                for (int j = i; j < n; ++j) {
                    const int index = s[j] - 'a';
                    if (!node->next[index])
                        break;

                    node = node->next[index];
                    if (node->isEnd) {
                        dp[j] = true;
                    }
                }
            }
        }
        return dp[n - 1];
    }

    // DP + Hash Set
    bool approach1(const std::string& s, const std::vector<std::string>& wordDict)
    {
        // dp[i] = whether s[0:i) can be segmented according to the given dictionary
        // 0 X X X j-1 j X X X i-1 i
        // |<-dp[j]->| |<--word->|, word.size()=i-j
        // |<-------dp[i]------->|
        std::unordered_set<std::string> set(wordDict.begin(), wordDict.end());
        const int n = s.size();
        std::vector<int> dp(n + 1, false);
        dp[0] = true;
        for (int i = 1; i <= n; ++i) {
            for (int j = 0; j < i; ++j) {
                if (dp[j] && set.count(s.substr(j, i - j))) {
                    dp[i] = true;
                    break;
                }
            }
        }
        return dp[n];
    }
};