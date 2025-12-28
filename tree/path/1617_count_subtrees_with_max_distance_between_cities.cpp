#include <vector>

/**
 * There are n cities numbered from 1 to n. You are given an array edges of size n-1, where edges[i]
 * = [ui, vi] represents a bidirectional edge between cities ui and vi. There exists a unique path
 * between each pair of cities. In other words, the cities form a tree.
 *
 * A subtree is a subset of cities where every city is reachable from every other city in the
 * subset, where the path between each pair passes through only the cities from the subset. Two
 * subtrees are different if there is a city in one subtree that is not present in the other.
 *
 * For each d from 1 to n-1, find the number of subtrees in which the maximum distance between any
 * two cities in the subtree is equal to d.
 *
 * Return an array of size n-1 where the dth element (1-indexed) is the number of subtrees in which
 * the maximum distance between any two cities is equal to d.
 *
 * Notice that the distance between the two cities is the number of edges in the path between them.
 *
 * ! 2 <= n <= 15
 * ! edges.length == n-1
 * ! edges[i].length == 2
 * ! 1 <= ui, vi <= n
 * ! All pairs (ui, vi) are distinct.
 */

class Solution {
public:
    std::vector<int> countSubgraphsForEachDiameter(int n, std::vector<std::vector<int>>& edges)
    {
        Graph graph(n);
        for (const auto& edge : edges) {
            const auto v = edge[0] - 1; // to 0-indexed
            const auto w = edge[1] - 1; // to 0-indexed
            graph[v].push_back(w);
            graph[w].push_back(v);
        }
        std::vector<int> result(n, 0);
        for (int subsetMask = 0; subsetMask < (1 << n); ++subsetMask) {
            // the subset must have at least two vertices
            // i.e., it has at least two binary ones
            if ((subsetMask & (subsetMask - 1)) == 0)
                continue;

            // compute the diameter of the subtree represented by the "subset"
            // #NOTE# diameter = length of the longest path = number of edges along the path
            int diameter = 0;
            int visitedMask = 0;
            // get one of the node in the subset to start our DFS
            dfs(diameter, visitedMask, subsetMask, countTrailingZeros(subsetMask), graph);
            if (visitedMask == subsetMask) {
                result[diameter]++;
            }
        }
        result.erase(result.begin());
        return result;
    }

private:
    using Graph = std::vector<std::vector<int>>;

    int countTrailingZeros(int val)
    {
        int mask = val & -val; // keep the last binary one and set the other bits to 0
        int count = 0;
        while ((mask & 1) == 0) {
            count++;
            mask >>= 1;
        }
        return count;
    }

    int dfs(int& diameter, int& visitedMask, int subsetMask, int root, const Graph& graph)
    {
        const int rootMask = 1 << root;
        visitedMask |= rootMask; // mark as visited
        int longest = 0;
        int secondLongest = 0;
        for (const auto& child : graph[root]) {
            const int childMask = 1 << child;
            if (visitedMask & childMask)
                continue;

            if (subsetMask & childMask) {
                const auto length = dfs(diameter, visitedMask, subsetMask, child, graph);
                if (length > longest) {
                    secondLongest = longest;
                    longest = length;
                } else if (length > secondLongest) {
                    secondLongest = length;
                }
            }
        }
        diameter = std::max(diameter, longest + secondLongest);
        return 1 + std::max(longest, secondLongest);
    }
};