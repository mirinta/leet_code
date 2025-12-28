#include <algorithm>
#include <vector>

/**
 * There are n people in a social group labeled from 0 to n - 1. You are given an array logs where
 * logs[i] = [timestampi, xi, yi] indicates that xi and yi will be friends at the time timestampi.
 *
 * Friendship is symmetric. That means if a is friends with b, then b is friends with a. Also,
 * person a is acquainted with a person b if a is friends with b, or a is a friend of someone
 * acquainted with b.
 *
 * Return the earliest time for which every person became acquainted with every other person. If
 * there is no such earliest time, return -1.
 *
 * ! 2 <= n <= 100
 * ! 1 <= logs.length <= 10^4
 * ! logs[i].length == 3
 * ! 0 <= timestampi <= 10^9
 * ! 0 <= xi, yi <= n - 1
 * ! xi != yi
 * ! All the values timestampi are unique.
 * ! All the pairs (xi, yi) occur at most one time in the input.
 */

class UnionFind {
public:
    explicit UnionFind(int n) : count(n), root(n), size(n, 1)
    {
        for (int i = 0; i < n; ++i) {
            root[i] = i;
        }
    }

    int numOfConnectedComponents()
    {
        return count;
    }

    int find(int x)
    {
        if (root[x] != x) {
            root[x] = find(root[x]);
        }
        return root[x];
    }

    bool connect(int p, int q)
    {
        int rootP = find(p);
        int rootQ = find(q);
        if (rootP == rootQ)
            return false;

        if (size[rootQ] > size[rootP]) {
            std::swap(rootP, rootQ);
        }
        root[rootQ] = rootP;
        size[rootP] += size[rootQ];
        count--;
        return true;
    }

private:
    int count;
    std::vector<int> root;
    std::vector<int> size;
};

class Solution {
public:
    int earliestAcq(std::vector<std::vector<int>>& logs, int n)
    {
        std::sort(logs.begin(), logs.end(), [](const auto& v1, const auto& v2) { return v1[0] < v2[0]; });
        UnionFind uf(n);
        for (const auto& v : logs) {
            uf.connect(v[1], v[2]);
            if (uf.numOfConnectedComponents() == 1)
                return v[0];
        }
        return -1;
    }
};