#include <algorithm>
#include <cmath>
#include <vector>

/**
 * There exist two undirected trees with n and m nodes, numbered from 0 to n - 1 and from 0 to m -
 * 1, respectively. You are given two 2D integer arrays edges1 and edges2 of lengths n - 1 and m -
 * 1, respectively, where edges1[i] = [ai, bi] indicates that there is an edge between nodes ai and
 * bi in the first tree and edges2[i] = [ui, vi] indicates that there is an edge between nodes ui
 * and vi in the second tree.
 *
 * You must connect one node from the first tree with another node from the second tree with an
 * edge.
 *
 * Return the minimum possible diameter of the resulting tree.
 *
 * The diameter of a tree is the length of the longest path between any two nodes in the tree.
 *
 * ! 1 <= n, m <= 10^5
 * ! edges1.length == n - 1
 * ! edges2.length == m - 1
 * ! edges1[i].length == edges2[i].length == 2
 * ! edges1[i] = [ai, bi]
 * ! 0 <= ai, bi < n
 * ! edges2[i] = [ui, vi]
 * ! 0 <= ui, vi < m
 * ! The input is generated such that edges1 and edges2 represent valid trees.
 */

class Solution {
public:
    int minimumDiameterAfterMerge(std::vector<std::vector<int>>& edges1, std::vector<std::vector<int>>& edges2)
    {
        // case 1: tree1 is much larger than tree2
        const int d1 = treeDiameter(edges1);
        // case 2: tree2 is much larger than tree1
        const int d2 = treeDiameter(edges2);
        // case 3: pick the middle node of tree1's diameter path
        //         pick the middle node of tree2's diameter path
        const int d3 = std::ceil(0.5 * d1) + std::ceil(0.5 * d2) + 1;
        return std::max({d1, d2, d3});
    }

private:
    // same as LC.1245
    int treeDiameter(const std::vector<std::vector<int>>& edges)
    {
        const int n = edges.size() + 1;
        std::vector<std::vector<int>> graph(n);
        for (const auto& edge : edges) {
            graph[edge[0]].push_back(edge[1]);
            graph[edge[1]].push_back(edge[0]);
        }
        int result = 0;
        dfs(result, 0, -1, graph);
        return result;
    }

    int dfs(int& result, int root, int parent, const std::vector<std::vector<int>>& graph)
    {
        int maxDepth = 0;
        int secondMaxDepth = 0;
        for (const auto& child : graph[root]) {
            if (child == parent)
                continue;

            const int depth = 1 + dfs(result, child, root, graph);
            if (depth > maxDepth) {
                std::swap(maxDepth, secondMaxDepth);
                maxDepth = depth;
            } else if (depth > secondMaxDepth) {
                secondMaxDepth = depth;
            }
        }
        result = std::max(result, maxDepth + secondMaxDepth);
        return maxDepth;
    }
};
