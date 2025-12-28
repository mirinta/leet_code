#include <vector>

/**
 * There is an undirected connected tree with n nodes labeled from 0 to n - 1 and n - 1 edges.
 *
 * You are given the integer n and the array edges where edges[i] = [ai, bi] indicates that there is
 * an edge between nodes ai and bi in the tree.
 *
 * Return an array answer of length n where answer[i] is the sum of the distances between the ith
 * node in the tree and all other nodes.
 *
 * ! 1 <= n <= 3 * 10^4
 * ! edges.length == n - 1
 * ! edges[i].length == 2
 * ! 0 <= ai, bi < n
 * ! ai != bi
 * ! The given input represents a valid tree.
 */

class Solution {
public:
    std::vector<int> sumOfDistancesInTree(int n, std::vector<std::vector<int>>& edges)
    {
        graph = std::vector<std::vector<int>>(n);
        for (const auto& e : edges) {
            graph[e[0]].push_back(e[1]);
            graph[e[1]].push_back(e[0]);
        }
        count = std::vector<int>(n);
        dfs1(0, -1);
        std::vector<int> result(n);
        result[0] = dfs2(0, -1);
        dfs3(result, 0, -1, n);
        return result;
    }

private:
    std::vector<std::vector<int>> graph;
    std::vector<int> count;

    // total num of nodes in "root"
    int dfs1(int root, int parent)
    {
        count[root] = 1;
        for (const auto& child : graph[root]) {
            if (child == parent)
                continue;

            count[root] += dfs1(child, root);
        }
        return count[root];
    }

    // sum of distances between "root" and all its children
    int dfs2(int root, int parent)
    {
        int dist = 0;
        for (const auto& child : graph[root]) {
            if (child == parent)
                continue;

            dist += dfs2(child, root) + count[child];
        }
        return dist;
    }

    void dfs3(std::vector<int>& result, int root, int parent, int n)
    {
        for (const auto& child : graph[root]) {
            if (child == parent)
                continue;

            result[child] = result[root] - count[child] + (n - count[child]);
            dfs3(result, child, root, n);
        }
    }
};