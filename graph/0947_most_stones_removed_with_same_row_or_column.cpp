#include <vector>

/**
 * On a 2D plane, we place n stones at some integer coordinate points. Each coordinate point may
 * have at most one stone.
 *
 * A stone can be removed if it shares either the same row or the same column as another stone that
 * has not been removed.
 *
 * Given an array stones of length n where stones[i] = [xi, yi] represents the location of the ith
 * stone, return the largest possible number of stones that can be removed.
 *
 * ! 1 <= stones.length <= 1000
 * ! 0 <= xi, yi <= 10^4
 * ! No two stones are at the same coordinate point.
 */

class UnionFind {
public:
    explicit UnionFind(int n) : count(n), root(n), size(n, 1)
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
        count--;
    }

    int numOfConnectedComponents()
    {
        return count;
    }

private:
    int count;
    std::vector<int> root;
    std::vector<int> size;
};

class Solution {
public:
    int removeStones(std::vector<std::vector<int>>& stones)
    {
        // stones[i] and stones[j] belong to the same group
        // if they share the same row or the same column
        //
        // for each group, let the num of stones of this group = K
        // then we can remove at most K-1 stones
        //
        // assume there are M groups, and the ith group has ki stones
        // then answer = (k1-1) + (k2-1) + ... + (km-1) = (k1+...+km) - M
        // since k1+k2+...+km = N, which is the total num of stones
        // thus, answer = N - M
        const int n = stones.size();
        UnionFind uf(n);
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (stones[i][0] == stones[j][0] || stones[i][1] == stones[j][1]) {
                    uf.connect(i, j);
                }
            }
        }
        return n - uf.numOfConnectedComponents();
    }
};