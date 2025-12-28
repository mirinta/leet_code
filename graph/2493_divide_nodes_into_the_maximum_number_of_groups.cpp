#include <queue>
#include <unordered_map>
#include <vector>

/**
 * You are given a positive integer n representing the number of nodes in an undirected graph. The
 * nodes are labeled from 1 to n.
 *
 * You are also given a 2D integer array edges, where edges[i] = [ai, bi] indicates that there is a
 * bidirectional edge between nodes ai and bi. Notice that the given graph may be disconnected.
 *
 * Divide the nodes of the graph into m groups (1-indexed) such that:
 *
 * - Each node in the graph belongs to exactly one group.
 *
 * - For every pair of nodes in the graph that are connected by an edge [ai, bi], if ai belongs to
 * the group with index x, and bi belongs to the group with index y, then |y - x| = 1.
 *
 * Return the maximum number of groups (i.e., maximum m) into which you can divide the nodes. Return
 * -1 if it is impossible to group the nodes with the given conditions.
 *
 * ! 1 <= n <= 500
 * ! 1 <= edges.length <= 10^4
 * ! edges[i].length == 2
 * ! 1 <= ai, bi <= n
 * ! ai != bi
 * ! There is at most one edge between any pair of vertices.
 */

class UnionFind {
public:
    explicit UnionFind(int n) : root(n), size(n, 1)
    {
        for (int i = 0; i < n; ++i) {
            root[i] = i;
        }
    }

    int find(int x)
    {
        if (x != root[x]) {
            root[x] = find(root[x]);
        }
        return root[x];
    }

    void connect(int p, int q)
    {
        int rootP = find(p);
        int rootQ = find(q);
        if (rootP == rootQ)
            return;

        if (size[rootQ] > size[rootP]) {
            std::swap(rootP, rootQ);
        }
        root[rootQ] = rootP;
        size[rootP] += size[rootQ];
    }

    int sizeOf(int x)
    {
        return size[find(x)];
    }

private:
    std::vector<int> root;
    std::vector<int> size;
};

class Solution {
public:
    int magnificentSets(int n, std::vector<std::vector<int>>& edges)
    {
        // nodes in the same group can't be connected by any edge
        std::vector<std::vector<int>> graph(n + 1);
        UnionFind uf(n + 1);
        for (const auto& e : edges) {
            uf.connect(e[0], e[1]);
            graph[e[0]].push_back(e[1]);
            graph[e[1]].push_back(e[0]);
        }
        std::vector<int> level(n + 1, 0); // start from 1
        std::unordered_map<int, int> map; // max num of groups of each independent graph
        for (int root = 1; root <= n; ++root) {
            std::fill(level.begin(), level.end(), 0);
            level[root] = 1;
            std::queue<int> queue;
            queue.emplace(root);
            int maxGroups = 0;
            while (!queue.empty()) {
                const auto v = queue.front();
                queue.pop();
                maxGroups = std::max(maxGroups, level[v]);
                for (const auto& adj : graph[v]) {
                    if (level[adj] == level[v])
                        return -1;

                    if (level[adj] == 0) {
                        level[adj] = level[v] + 1;
                        queue.emplace(adj);
                    }
                }
            }
            map[uf.find(root)] = std::max(map[uf.find(root)], maxGroups);
        }
        int result = 0;
        for (const auto& [_, count] : map) {
            result += count;
        }
        return result;
    }
};