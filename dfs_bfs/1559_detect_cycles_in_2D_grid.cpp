#include <vector>

/**
 * Given a 2D array of characters grid of size m x n, you need to find if there exists any cycle
 * consisting of the same value in grid.
 *
 * A cycle is a path of length 4 or more in the grid that starts and ends at the same cell. From a
 * given cell, you can move to one of the cells adjacent to it - in one of the four directions (up,
 * down, left, or right), if it has the same value of the current cell.
 *
 * Also, you cannot move to the cell that you visited in your last move. For example, the cycle (1,
 * 1) -> (1, 2) -> (1, 1) is invalid because from (1, 2) we visited (1, 1) which was the last
 * visited cell.
 *
 * Return true if any cycle of the same value exists in grid, otherwise, return false.
 *
 * ! m == grid.length
 * ! n == grid[i].length
 * ! 1 <= m, n <= 500
 * ! grid consists only of lowercase English letters.
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
        return true;
    }

private:
    std::vector<int> root;
    std::vector<int> size;
};

class Solution {
public:
    bool containsCycle(std::vector<std::vector<char>>& grid)
    {
        const int m = grid.size();
        const int n = grid[0].size();
        auto encode = [&](int i, int j) { return n * i + j; };
        UnionFind uf(m * n);
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i + 1 < m && grid[i][j] == grid[i + 1][j] && !uf.connect(encode(i, j), encode(i + 1, j)))
                    return true;

                if (j + 1 < n && grid[i][j] == grid[i][j + 1] && !uf.connect(encode(i, j), encode(i, j + 1)))
                    return true;
            }
        }
        return false;
    }
};