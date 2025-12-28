#include <unordered_set>
#include <vector>

/**
 * You are given an n x n binary matrix grid. You are allowed to change at most one 0 to be 1.
 *
 * Return the size of the largest island in grid after applying this operation.
 *
 * An island is a 4-directionally connected group of 1s.
 *
 * ! n == grid.length
 * ! n == grid[i].length
 * ! 1 <= n <= 500
 * ! grid[i][j] is either 0 or 1.
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
    int largestIsland(std::vector<std::vector<int>>& grid)
    {
        static const std::vector<std::pair<int, int>> kDirections{{1, 0}, {-1, 0}, {0, -1}, {0, 1}};
        const int n = grid.size();
        auto encode = [&](int i, int j) { return j + i * n; };
        UnionFind uf(n * n);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (!grid[i][j])
                    continue;

                for (const auto& [dx, dy] : kDirections) {
                    const int x = i + dx;
                    const int y = j + dy;
                    if (x < 0 || x >= n || y < 0 || y >= n || !grid[x][y])
                        continue;

                    uf.connect(encode(i, j), encode(x, y));
                }
            }
        }
        std::unordered_set<int> set;
        int result = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j]) {
                    result = std::max(result, uf.sizeOf(encode(i, j)));
                    continue;
                }
                int area = 1;
                set.clear();
                for (const auto& [dx, dy] : kDirections) {
                    const int x = i + dx;
                    const int y = j + dy;
                    if (x < 0 || x >= n || y < 0 || y >= n || !grid[x][y])
                        continue;

                    if (set.insert(uf.find(encode(x, y))).second) {
                        area += uf.sizeOf(encode(x, y));
                    }
                }
                result = std::max(result, area);
            }
        }
        return result;
    }
};
