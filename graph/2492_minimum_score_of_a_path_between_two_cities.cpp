#include <queue>
#include <vector>

/**
 * You are given a positive integer n representing n cities numbered from 1 to n. You are also given a 2D array roads
 * where roads[i] = [ai, bi, distancei] indicates that there is a bidirectional road between cities ai and bi with a
 * distance equal to distancei. The cities graph is not necessarily connected.
 *
 * The score of a path between two cities is defined as the minimum distance of a road in this path.
 *
 * Return the minimum possible score of a path between cities 1 and n.
 *
 * Note:
 *
 * - A path is a sequence of roads between two cities.
 *
 * - It is allowed for a path to contain the same road multiple times, and you can visit cities 1 and n multiple times
 * along the path.
 *
 * - The test cases are generated such that there is at least one path between 1 and n.
 *
 * ! 2 <= n <= 10^5
 * ! 1 <= roads.length <= 10^5
 * ! roads[i].length == 3
 * ! 1 <= ai, bi <= n
 * ! ai != bi
 * ! 1 <= distancei <= 10^4
 * ! There are no repeated edges.
 * ! There is at least one path between 1 and n.
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

    bool isConnected(int p, int q)
    {
        return find(p) == find(q);
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

private:
    std::vector<int> root;
    std::vector<int> size;
};

class Solution {
public:
    int minScore(int n, std::vector<std::vector<int>>& roads)
    {
        return approach2(n, roads);
    }

private:
    int approach2(int n, const std::vector<std::vector<int>>& roads)
    {
        UnionFind uf(n + 1);
        for (const auto& r : roads) {
            uf.connect(r[0], r[1]);
        }
        int result = INT_MAX;
        for (const auto& r : roads) {
            if (uf.isConnected(1, r[0])) {
                result = std::min(result, r[2]);
            }
        }
        return result;
    }

    int approach1(int n, const std::vector<std::vector<int>>& roads)
    {
        std::vector<std::vector<std::pair<int, int>>> graph(n);
        for (const auto& r : roads) {
            graph[r[0] - 1].emplace_back(r[1] - 1, r[2]);
            graph[r[1] - 1].emplace_back(r[0] - 1, r[2]);
        }
        std::vector<bool> visited(n, false);
        visited[0] = true;
        std::queue<int> queue;
        queue.emplace(0);
        int result = INT_MAX;
        while (!queue.empty()) {
            const auto v = queue.front();
            queue.pop();
            for (const auto& [w, dist] : graph[v]) {
                result = std::min(result, dist);
                if (!visited[w]) {
                    visited[w] = true;
                    queue.emplace(w);
                }
            }
        }
        return result;
    }
};