#include <vector>

/**
 * You are given an integer n representing the number of nodes in a graph, labeled from 0 to n - 1.
 *
 * You are also given an integer array nums of length n sorted in non-decreasing order, and an integer maxDiff.
 *
 * An undirected edge exists between nodes i and j if the absolute difference between nums[i] and nums[j] is at most
 * maxDiff (i.e., |nums[i] - nums[j]| <= maxDiff).
 *
 * You are also given a 2D integer array queries. For each queries[i] = [ui, vi], determine whether there exists a path
 * between nodes ui and vi.
 *
 * Return a boolean array answer, where answer[i] is true if there exists a path between ui and vi in the ith query and
 * false otherwise.
 *
 * ! 1 <= n == nums.length <= 10^5
 * ! 0 <= nums[i] <= 10^5
 * ! nums is sorted in non-decreasing order.
 * ! 0 <= maxDiff <= 10^5
 * ! 1 <= queries.length <= 10^5
 * ! queries[i] == [ui, vi]
 * ! 0 <= ui, vi < n
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
        if (root[x] != x) {
            root[x] = find(root[x]);
        }
        return root[x];
    }

    bool connected(int p, int q)
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
    std::vector<bool>
        pathExistenceQueries(int n, std::vector<int>& nums, int maxDiff, std::vector<std::vector<int>>& queries)
    {
        UnionFind uf(n);
        for (int i = 1; i < n; ++i) {
            if (nums[i] - nums[i - 1] <= maxDiff) {
                uf.connect(i, i - 1);
            }
        }
        std::vector<bool> result;
        result.reserve(queries.size());
        for (const auto& q : queries) {
            result.emplace_back(uf.connected(q[0], q[1]));
        }
        return result;
    }
};