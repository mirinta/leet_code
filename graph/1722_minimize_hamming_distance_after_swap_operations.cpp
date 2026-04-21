#include <unordered_map>
#include <vector>

/**
 * You are given two integer arrays, source and target, both of length n. You are also given an array allowedSwaps where
 * each allowedSwaps[i] = [ai, bi] indicates that you are allowed to swap the elements at index ai and index bi
 * (0-indexed) of array source. Note that you can swap elements at a specific pair of indices multiple times and in any
 * order.
 *
 * The Hamming distance of two arrays of the same length, source and target, is the number of positions where the
 * elements are different. Formally, it is the number of indices i for 0 <= i <= n-1 where source[i] != target[i]
 * (0-indexed).
 *
 * Return the minimum Hamming distance of source and target after performing any amount of swap operations on array
 * source.
 *
 * ! n == source.length == target.length
 * ! 1 <= n <= 10^5
 * ! 1 <= source[i], target[i] <= 10^5
 * ! 0 <= allowedSwaps.length <= 10^5
 * ! allowedSwaps[i].length == 2
 * ! 0 <= ai, bi <= n - 1
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
        if (root[x] != x) {
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

private:
    std::vector<int> root;
    std::vector<int> size;
};

class Solution {
public:
    int minimumHammingDistance(std::vector<int>& source,
                               std::vector<int>& target,
                               std::vector<std::vector<int>>& allowedSwaps)
    {
        const int n = source.size();
        UnionFind uf(n);
        for (const auto& op : allowedSwaps) {
            uf.connect(op[0], op[1]);
        }
        std::unordered_map<int, std::unordered_map<int, int>> map;
        for (int i = 0; i < n; ++i) {
            map[uf.find(i)][source[i]]++;
        }
        int result = 0;
        for (int i = 0; i < n; ++i) {
            result += --map[uf.find(i)][target[i]] < 0;
        }
        return result;
    }
};