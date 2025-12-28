#include <string>
#include <vector>

/**
 * You are given a tree (i.e. a connected, undirected graph that has no cycles) rooted at node 0
 * consisting of n nodes numbered from 0 to n - 1. The tree is represented by a 0-indexed array
 * parent of size n, where parent[i] is the parent of node i. Since node 0 is the root, parent[0] ==
 * -1.
 *
 * You are also given a string s of length n, where s[i] is the character assigned to node i.
 *
 * Return the length of the longest path in the tree such that no pair of adjacent nodes on the path
 * have the same character assigned to them.
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
    int longestPath(std::vector<int>& parent, std::string& s)
    {
        const int n = parent.size();
        std::vector<std::vector<int>> graph(n);
        for (int i = 0; i < n; ++i) {
            if (parent[i] == -1)
                continue; // the root node has no parent

            // parent[i] = j means that j is the parent of i
            graph[parent[i]].push_back(i);
        }
        int result = 0;
        dfs(result, 0, graph, s);
        return result;
    }

    int dfs(int& result, int root, const std::vector<std::vector<int>>& graph, const std::string& s)
    {
        // length of a path = number of nodes along the path
        // #NOTE# The given tree may be a N-ary tree.
        int longestSubtreePath = 0;
        int secondLongestSubtreePath = 0;
        for (const auto& child : graph[root]) {
            const int path = dfs(result, child, graph, s);
            if (s[root] == s[child])
                continue;

            if (path > longestSubtreePath) {
                secondLongestSubtreePath = longestSubtreePath;
                longestSubtreePath = path;
            } else if (path > secondLongestSubtreePath) {
                secondLongestSubtreePath = path;
            }
        }
        result = std::max(result, longestSubtreePath + secondLongestSubtreePath + 1); // +1 to include the root node
        return longestSubtreePath + 1;                                                // +1 to include the root node
    }
};