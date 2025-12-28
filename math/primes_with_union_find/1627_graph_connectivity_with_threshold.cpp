#include <vector>

/**
 * We have n cities labeled from 1 to n. Two different cities with labels x and y are directly
 * connected by a bidirectional road if and only if x and y share a common divisor strictly greater
 * than some threshold. More formally, cities with labels x and y have a road between them if there
 * exists an integer z such that all of the following are true:
 *
 * - x % z == 0,
 *
 * - y % z == 0, and
 *
 * - z > threshold.
 *
 * Given the two integers, n and threshold, and an array of queries, you must determine for each
 * queries[i] = [ai, bi] if cities ai and bi are connected directly or indirectly. (i.e. there is
 * some path between them).
 *
 * Return an array answer, where answer.length == queries.length and answer[i] is true if for the
 * ith query, there is a path between ai and bi, or answer[i] is false if there is no path.
 *
 * ! 2 <= n <= 10^4
 * ! 0 <= threshold <= n
 * ! 1 <= queries.length <= 10^5
 * ! queries[i].length == 2
 * ! 1 <= ai, bi <= cities
 * ! ai != bi
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
        const int rootP = find(p);
        const int rootQ = find(q);
        if (rootP == rootQ)
            return;

        if (size[rootQ] > size[rootP]) {
            root[rootP] = rootQ;
            size[rootQ] += size[rootP];
        } else {
            root[rootQ] = rootP;
            size[rootP] += size[rootQ];
        }
    }

private:
    std::vector<int> root;
    std::vector<int> size;
};

class Solution {
public:
    std::vector<bool> areConnected(int n, int threshold, std::vector<std::vector<int>>& queries)
    {
        UnionFind uf(n + 1);
        for (int divisor = threshold + 1; divisor <= n; ++divisor) {
            for (int x = 2 * divisor; x <= n; x += divisor) {
                uf.connect(divisor, x);
            }
        }
        std::vector<bool> result;
        result.reserve(queries.size());
        for (const auto& query : queries) {
            result.push_back(uf.isConnected(query[0], query[1]));
        }
        return result;
    }
};