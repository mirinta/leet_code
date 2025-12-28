#include <array>
#include <string>
#include <unordered_map>
#include <vector>

/**
 * You are given two 0-indexed strings source and target, both of length n and consisting of
 * lowercase English characters. You are also given two 0-indexed string arrays original and
 * changed, and an integer array cost, where cost[i] represents the cost of converting the string
 * original[i] to the string changed[i].
 *
 * You start with the string source. In one operation, you can pick a substring x from the string,
 * and change it to y at a cost of z if there exists any index j such that cost[j] == z, original[j]
 * == x, and changed[j] == y. You are allowed to do any number of operations, but any pair of
 * operations must satisfy either of these two conditions:
 *
 * The substrings picked in the operations are source[a..b] and source[c..d] with either b < c or d
 * < a. In other words, the indices picked in both operations are disjoint. The substrings picked in
 * the operations are source[a..b] and source[c..d] with a == c and b == d. In other words, the
 * indices picked in both operations are identical. Return the minimum cost to convert the string
 * source to the string target using any number of operations. If it is impossible to convert source
 * to target, return -1.
 *
 * Note that there may exist indices i, j such that original[j] == original[i] and changed[j] ==
 * changed[i].
 *
 * ! 1 <= source.length == target.length <= 1000
 * ! source, target consist only of lowercase English characters.
 * ! 1 <= cost.length == original.length == changed.length <= 100
 * ! 1 <= original[i].length == changed[i].length <= source.length
 * ! original[i], changed[i] consist only of lowercase English characters.
 * ! original[i] != changed[i]
 * ! 1 <= cost[i] <= 10^6
 */

class Solution {
public:
    long long minimumCost(std::string source,
                          std::string target,
                          std::vector<std::string>& original,
                          std::vector<std::string>& changed,
                          std::vector<int>& cost)
    {
        if (source.size() != target.size())
            return -1;

        std::unordered_map<std::string, int> map;
        for (const auto& s : original) {
            if (!map.count(s)) {
                map[s] = map.size();
            }
        }
        for (const auto& s : changed) {
            if (!map.count(s)) {
                map[s] = map.size();
            }
        }
        const int numOfNodes = map.size();
        std::vector<std::vector<long long>> minDist(numOfNodes, std::vector<long long>(numOfNodes, LLONG_MAX));
        for (int i = 0; i < numOfNodes; ++i) {
            minDist[i][i] = 0;
        }
        for (int i = 0; i < cost.size(); ++i) {
            const int from = map[original[i]];
            const int to = map[changed[i]];
            minDist[from][to] = std::min<long long>(minDist[from][to], cost[i]);
        }
        for (int k = 0; k < numOfNodes; ++k) {
            for (int i = 0; i < numOfNodes; ++i) {
                if (minDist[i][k] == LLONG_MAX)
                    continue;

                for (int j = 0; j < numOfNodes; ++j) {
                    if (minDist[k][j] == LLONG_MAX)
                        continue;

                    minDist[i][j] = std::min(minDist[i][j], minDist[i][k] + minDist[k][j]);
                }
            }
        }
        // dp[i] = min cost of changing source[0:i) to target[0:i)
        // X X X X j-1 j X X X X X X X X i
        // |<-dp[j]->| |<-can change?->|
        // |<----------dp[i]---------->|
        TrieNode root;
        for (const auto& [s, id] : map) {
            auto* node = &root;
            for (auto iter = s.rbegin(); iter != s.rend(); ++iter) {
                const int index = (*iter) - 'a';
                if (!node->next[index]) {
                    node->next[index] = new TrieNode();
                }
                node = node->next[index];
            }
            node->id = id;
        }
        const int n = source.size();
        std::vector<long long> dp(n + 1, LLONG_MAX);
        dp[0] = 0;
        for (int i = 1; i <= n; ++i) {
            if (source[i - 1] == target[i - 1]) {
                dp[i] = dp[i - 1];
            }
            auto* node1 = &root;
            auto* node2 = &root;
            for (int j = i - 1; j >= 0; --j) {
                const int index1 = source[j] - 'a';
                const int index2 = target[j] - 'a';
                if (!node1->next[index1] || !node2->next[index2])
                    break;

                node1 = node1->next[index1];
                node2 = node2->next[index2];
                const int from = node1->id;
                const int to = node2->id;
                if (from >= 0 && to >= 0 && minDist[from][to] != LLONG_MAX && dp[j] != LLONG_MAX) {
                    dp[i] = std::min(dp[i], dp[j] + minDist[from][to]);
                }
            }
        }
        return dp[n] == LLONG_MAX ? -1 : dp[n];
    }

private:
    struct TrieNode {
        std::array<TrieNode*, 26> next{nullptr};
        int id{-1};
    };
};