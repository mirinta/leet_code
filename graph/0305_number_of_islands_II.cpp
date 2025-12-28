#include <unordered_set>
#include <vector>

/**
 * You are given an empty 2D binary grid grid of size m x n. The grid represents a map where 0's
 * represent water and 1's represent land. Initially, all the cells of grid are water cells (i.e.,
 * all the cells are 0's).
 *
 * We may perform an add land operation which turns the water at position into a land. You are given
 * an array positions where positions[i] = [ri, ci] is the position (ri, ci) at which we should
 * operate the ith operation.
 *
 * Return an array of integers answer where answer[i] is the number of islands after turning the
 * cell (ri, ci) into a land.
 *
 * An island is surrounded by water and is formed by connecting adjacent lands horizontally or
 * vertically. You may assume all four edges of the grid are all surrounded by water.
 *
 * ! 1 <= m, n, positions.length <= 10^4
 * ! 1 <= m * n <= 10^4
 * ! positions[i].length == 2
 * ! 0 <= ri < m
 * ! 0 <= ci < n
 */

class UnionFind {
public:
    explicit UnionFind(int n) : n(n), root(n), rank(n, 1)
    {
        for (int i = 0; i < n; ++i) {
            root[i] = i;
        }
    }

    int count()
    {
        return n;
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

        if (rank[rootQ] > rank[rootP]) {
            std::swap(rootP, rootQ);
        }
        root[rootQ] = rootP;
        rank[rootP] += rank[rootQ];
        n--;
    }

private:
    int n;
    std::vector<int> root;
    std::vector<int> rank;
};

class Solution {
public:
    std::vector<int> numIslands2(int m, int n, std::vector<std::vector<int>>& positions)
    {
        const int total = m * n;
        UnionFind uf(total);
        std::unordered_set<int> lands;
        std::vector<int> result(positions.size());
        for (int i = 0; i < positions.size(); ++i) {
            const int x = positions[i][0];
            const int y = positions[i][1];
            const int pos = encode(x, y, n);
            for (const auto& [dx, dy] : kDirections) {
                const int newX = x + dx;
                const int newY = y + dy;
                if (newX < 0 || newX >= m || newY < 0 || newY >= n)
                    continue;

                if (const int adj = encode(newX, newY, n); lands.count(adj)) {
                    uf.connect(pos, adj);
                }
            }
            lands.insert(pos);
            result[i] = uf.count() - (total - lands.size());
        }
        return result;
    }

private:
    static const std::vector<std::pair<int, int>> kDirections;

    int encode(int x, int y, int n)
    {
        return x * n + y;
    }
};
const std::vector<std::pair<int, int>> Solution::kDirections{{0, 1}, {0, -1}, {1, 0}, {-1, 0}};