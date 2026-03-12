#include <functional>
#include <unordered_map>
#include <vector>

/**
 * You are given a tree (i.e. a connected, undirected graph that has no cycles) rooted at node 0 consisting of n nodes
 * numbered from 0 to n - 1. The tree is represented by a 0-indexed array parent of size n, where parent[i] is the
 * parent of node i. Since node 0 is the root, parent[0] == -1.
 *
 * You are also given a string s of length n, where s[i] is the character assigned to the edge between i and parent[i].
 * s[0] can be ignored.
 *
 * Return the number of pairs of nodes (u, v) such that u < v and the characters assigned to edges on the path from u to
 * v can be rearranged to form a palindrome.
 *
 * A string is a palindrome when it reads the same backwards as forwards.
 *
 * ! n == parent.length == s.length
 * ! 1 <= n <= 10^5
 * ! 0 <= parent[i] <= n - 1 for all i >= 1
 * ! parent[0] == -1
 * ! parent represents a valid tree.
 * ! s consists of only lowercase English letters.
 */

class Solution {
public:
    long long countPalindromePaths(std::vector<int>& parent, std::string& s)
    {
        // mask[i] = 0, if the number of character i is even
        // mask[i] = 1, if the number of character i is odd
        const int n = parent.size();
        std::vector<std::vector<std::pair<int, int>>> graph(n);
        for (int i = 1; i < n; ++i) {
            graph[parent[i]].emplace_back(i, s[i] - 'a');
        }
        std::unordered_map<int, long long> map;
        long long result = 0;
        std::function<void(int, int, int)> dfs = [&](int mask, int node, int parent) {
            if (map.count(mask)) {
                result += map[mask];
            }
            for (int shift = 0; shift < 26; ++shift) {
                const int target = mask ^ (1 << shift);
                if (map.count(target)) {
                    result += map[target];
                }
            }
            map[mask]++;
            for (const auto& [next, c] : graph[node]) {
                if (next == parent)
                    continue;

                dfs(mask ^ (1 << c), next, node);
            }
        };
        dfs(0, 0, -1);
        return result;
    }
};
