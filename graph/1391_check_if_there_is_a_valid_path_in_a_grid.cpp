#include <array>
#include <tuple>
#include <vector>

/**
 * You are given an m x n grid. Each cell of grid represents a street. The street of grid[i][j] can
 * be:
 *
 * - 1 which means a street connecting the left cell and the right cell.
 *
 * - 2 which means a street connecting the upper cell and the lower cell.
 *
 * - 3 which means a street connecting the left cell and the lower cell.
 *
 * - 4 which means a street connecting the right cell and the lower cell.
 *
 * - 5 which means a street connecting the left cell and the upper cell.
 *
 * - 6 which means a street connecting the right cell and the upper cell.
 *
 * ! m == grid.length
 * ! n == grid[i].length
 * ! 1 <= m, n <= 300
 * ! 1 <= grid[i][j] <= 6
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
    bool hasValidPath(std::vector<std::vector<int>>& grid)
    {
        static const auto info = []() {
            std::array<std::array<std::tuple<int, int, int>, 2>, 7> info{};
            // go up: 2, 3, 4
            // go down: 2, 5, 6
            // go left: 1, 4, 6
            // go right: 1, 3, 5
            const int up = (1 << 2) | (1 << 3) | (1 << 4);
            const int down = (1 << 2) | (1 << 5) | (1 << 6);
            const int left = (1 << 1) | (1 << 4) | (1 << 6);
            const int right = (1 << 1) | (1 << 3) | (1 << 5);
            info[1][0] = {0, 1, right};
            info[1][1] = {0, -1, left};
            info[2][0] = {1, 0, down};
            info[2][1] = {-1, 0, up};
            info[3][0] = {1, 0, down};
            info[3][1] = {0, -1, left};
            info[4][0] = {1, 0, down};
            info[4][1] = {0, 1, right};
            info[5][0] = {-1, 0, up};
            info[5][1] = {0, -1, left};
            info[6][0] = {-1, 0, up};
            info[6][1] = {0, 1, right};
            return info;
        }();
        const int m = grid.size();
        const int n = grid[0].size();
        auto encode = [&](int i, int j) { return i * n + j; };
        UnionFind uf(m * n);
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                for (const auto& [dx, dy, valid] : info[grid[i][j]]) {
                    const int x = i + dx;
                    const int y = j + dy;
                    if (x < 0 || x >= m || y < 0 || y >= n)
                        continue;

                    if (valid & (1 << grid[x][y])) {
                        uf.connect(encode(i, j), encode(x, y));
                    }
                }
            }
        }
        return uf.isConnected(0, m * n - 1);
    }
};