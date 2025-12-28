#include <queue>
#include <vector>

/**
 * There is a directed graph consisting of n nodes numbered from 0 to n - 1 and n directed edges.
 *
 * You are given a 0-indexed array edges where edges[i] indicates that there is an edge from node i
 * to node edges[i].
 *
 * Consider the following process on the graph:
 *
 * You start from a node x and keep visiting other nodes through edges until you reach a node that
 * you have already visited before on this same process. Return an array answer where answer[i] is
 * the number of different nodes that you will visit if you perform the process starting from node
 * i.
 *
 * ! n == edges.length
 * ! 2 <= n <= 10^5
 * ! 0 <= edges[i] <= n - 1
 * ! edges[i] != i
 */

class Solution {
public:
    std::vector<int> countVisitedNodes(std::vector<int>& edges)
    {
        const int n = edges.size();
        std::vector<std::vector<int>> reversedGraph(n);
        std::vector<int> indegree(n, 0);
        for (int i = 0; i < n; ++i) {
            indegree[edges[i]]++;
            reversedGraph[edges[i]].push_back(i);
        }
        std::queue<int> queue;
        for (int i = 0; i < n; ++i) {
            if (indegree[i] == 0) {
                queue.push(i);
            }
        }
        while (!queue.empty()) {
            const auto v = queue.front();
            queue.pop();
            if (--indegree[edges[v]] == 0) {
                queue.push(edges[v]);
            }
        }
        std::vector<int> result(n, 0);
        // after topological sorting,
        // if indegree[i] > 0, node i is in the cycle(s)
        for (int i = 0; i < n; ++i) {
            if (indegree[i] <= 0)
                continue;

            std::vector<int> ring;
            int v = i;
            while (true) {
                ring.push_back(v);
                indegree[v] = -1; // -1 as visited
                v = edges[v];
                if (v == i)
                    break;
            }
            for (const auto& node : ring) {
                dfs(result, node, ring.size(), indegree, reversedGraph);
            }
        }
        return result;
    }

private:
    void dfs(std::vector<int>& result,
             int node,
             int depth,
             const std::vector<int>& indegree,
             const std::vector<std::vector<int>>& graph)
    {
        result[node] = depth;
        for (const auto& w : graph[node]) {
            if (indegree[w] == 0) {
                dfs(result, w, depth + 1, indegree, graph);
            }
        }
    }
};