#include <queue>
#include <vector>

/**
 * A tree is an undirected graph in which any two vertices are connected by exactly one path. In
 * other words, any connected graph without simple cycles is a tree.
 *
 * Given a tree of n nodes labelled from 0 to n - 1, and an array of n - 1 edges where edges[i] =
 * [ai, bi] indicates that there is an undirected edge between the two nodes ai and bi in the tree,
 * you can choose any node of the tree as the root. When you select a node x as the root, the result
 * tree has height h. Among all possible rooted trees, those with minimum height (i.e. min(h))  are
 * called minimum height trees (MHTs).
 *
 * Return a list of all MHTs' root labels. You can return the answer in any order.
 *
 * The height of a rooted tree is the number of edges on the longest downward path between the root
 * and a leaf.
 *
 * ! 1 <= n <= 2 * 10^4
 * ! edges.length == n - 1
 * ! 0 <= ai, bi < n
 * ! ai != bi
 * ! All the pairs (ai, bi) are distinct.
 * ! The given input is guaranteed to be a tree and there will be no repeated edges.
 */

class Solution {
public:
    std::vector<int> findMinHeightTrees(int n, std::vector<std::vector<int>>& edges)
    {
        if (n == 1)
            return {0};

        if (n == 2)
            return {0, 1};

        std::vector<std::vector<int>> graph(n, std::vector<int>());
        std::vector<int> degrees(n, 0);
        for (const auto& edge : edges) {
            const int p = edge[0];
            const int q = edge[1];
            graph[p].push_back(q);
            graph[q].push_back(p);
            degrees[p]++;
            degrees[q]++;
        }
        std::queue<int> queue;
        for (int i = 0; i < n; ++i) {
            if (degrees[i] == 1) {
                queue.push(i);
            }
        }
        int count = n; // num of remaining nodes
        while (count > 2) {
            count -= queue.size();
            for (int k = queue.size(); k > 0; --k) {
                const int v = queue.front();
                queue.pop();
                for (const auto& adj : graph[v]) {
                    if (--degrees[adj] == 1) {
                        queue.push(adj);
                    }
                }
            }
        }
        std::vector<int> result;
        while (!queue.empty()) {
            result.push_back(queue.front());
            queue.pop();
        }
        return result;
    }
};