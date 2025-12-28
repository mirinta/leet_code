#include <functional>
#include <queue>
#include <vector>

/**
 * There exist two undirected trees with n and m nodes, with distinct labels in ranges [0, n - 1]
 * and [0, m - 1], respectively.
 *
 * You are given two 2D integer arrays edges1 and edges2 of lengths n - 1 and m - 1, respectively,
 * where edges1[i] = [ai, bi] indicates that there is an edge between nodes ai and bi in the first
 * tree and edges2[i] = [ui, vi] indicates that there is an edge between nodes ui and vi in the
 * second tree. You are also given an integer k.
 *
 * Node u is target to node v if the number of edges on the path from u to v is less than or equal
 * to k. Note that a node is always target to itself.
 *
 * Return an array of n integers answer, where answer[i] is the maximum possible number of nodes
 * target to node i of the first tree if you have to connect one node from the first tree to another
 * node in the second tree.
 *
 * Note that queries are independent from each other. That is, for every query you will remove the
 * added edge before proceeding to the next query.
 *
 * ! 2 <= n, m <= 1000
 * ! edges1.length == n - 1
 * ! edges2.length == m - 1
 * ! edges1[i].length == edges2[i].length == 2
 * ! edges1[i] = [ai, bi]
 * ! 0 <= ai, bi < n
 * ! edges2[i] = [ui, vi]
 * ! 0 <= ui, vi < m
 * ! The input is generated such that edges1 and edges2 represent valid trees.
 * ! 0 <= k <= 1000
 */

class Solution {
public:
    std::vector<int> maxTargetNodes(std::vector<std::vector<int>>& edges1, std::vector<std::vector<int>>& edges2, int k)
    {
        const auto graph2 = buildGraph(edges2);
        const std::vector<int> count2 = helper(graph2, k - 1);
        const int max2 = *std::max_element(count2.begin(), count2.end());
        const auto graph1 = buildGraph(edges1);
        std::vector<int> result = helper(graph1, k);
        for (auto& val : result) {
            val += max2;
        }
        return result;
    }

private:
    std::vector<std::vector<int>> buildGraph(const std::vector<std::vector<int>>& edges)
    {
        const int n = edges.size() + 1;
        std::vector<std::vector<int>> graph(n);
        for (const auto& e : edges) {
            graph[e[0]].push_back(e[1]);
            graph[e[1]].push_back(e[0]);
        }
        return graph;
    }

    std::vector<int> helper(const std::vector<std::vector<int>>& graph, int k)
    {
        std::function<int(int, int)> bfs = [&graph](int root, int k) {
            std::queue<std::pair<int, int>> queue; // <curr, parent>
            queue.emplace(root, -1);
            int result = 0;
            while (!queue.empty() && k >= 0) {
                k--;
                result += queue.size();
                for (int i = queue.size(); i > 0; --i) {
                    const auto [curr, parent] = queue.front();
                    queue.pop();
                    for (const auto& adj : graph[curr]) {
                        if (adj == parent)
                            continue;

                        queue.emplace(adj, curr);
                    }
                }
            }
            return result;
        };
        std::vector<int> result(graph.size());
        for (int i = 0; i < graph.size(); ++i) {
            result[i] = bfs(i, k);
        }
        return result;
    }
};
