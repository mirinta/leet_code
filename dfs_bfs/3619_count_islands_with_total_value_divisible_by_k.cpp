#include <array>
#include <functional>
#include <numeric>
#include <unordered_map>
#include <vector>

/**
 * You are given an m x n matrix grid and a positive integer k. An island is a group of positive integers (representing
 * land) that are 4-directionally connected (horizontally or vertically).
 *
 * The total value of an island is the sum of the values of all cells in the island.
 *
 * Return the number of islands with a total value divisible by k.
 *
 * ! m == grid.length
 * ! n == grid[i].length
 * ! 1 <= m, n <= 1000
 * ! 1 <= m * n <= 10^5
 * ! 0 <= grid[i][j] <= 10^6
 * ! 1 <= k <= 10^6
 */

class UnionFind {
public:
    explicit UnionFind(int n) : root(n), size(n, 1)
    {
        std::iota(root.begin(), root.end(), 0);
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
    int countIslands(std::vector<std::vector<int>>& grid, int k)
    {
        return approach2(grid, k);
    }

private:
    static constexpr std::array<std::pair<int, int>, 4> kDirections{{{1, 0}, {-1, 0}, {0, 1}, {0, -1}}};

    int approach2(const std::vector<std::vector<int>>& grid, int k)
    {
        const int m = grid.size();
        const int n = grid[0].size();
        auto encode = [&](int x, int y) { return x * n + y; };
        UnionFind uf(m * n);
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == 0)
                    continue;

                if (i + 1 < m && grid[i + 1][j] != 0) {
                    uf.connect(encode(i, j), encode(i + 1, j));
                }
                if (j + 1 < n && grid[i][j + 1] != 0) {
                    uf.connect(encode(i, j), encode(i, j + 1));
                }
            }
        }
        std::unordered_map<int, long long> map;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == 0)
                    continue;

                map[uf.find(encode(i, j))] += grid[i][j];
            }
        }
        int result = 0;
        for (const auto& [_, sum] : map) {
            result += sum % k == 0;
        }
        return result;
    }

    int approach1(const std::vector<std::vector<int>>& grid, int k)
    {
        const int m = grid.size();
        const int n = grid[0].size();
        std::vector<std::vector<bool>> visited(m, std::vector<bool>(n, false));
        std::function<long long(int, int)> dfs = [&](int x, int y) {
            visited[x][y] = true;
            long long sum = grid[x][y];
            for (const auto& [dx, dy] : kDirections) {
                const int i = x + dx;
                const int j = y + dy;
                if (i < 0 || i >= m || j < 0 || j >= n || grid[i][j] == 0 || visited[i][j])
                    continue;

                sum += dfs(i, j);
            }
            return sum;
        };
        int result = 0;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == 0 || visited[i][j])
                    continue;

                result += dfs(i, j) % k == 0;
            }
        }
        return result;
    }
};
