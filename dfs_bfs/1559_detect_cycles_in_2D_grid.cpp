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
    explicit UnionFind(int n) : root(n), rank(n, 1)
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

        if (rank[rootQ] > rank[rootP]) {
            std::swap(rootP, rootQ);
        }
        root[rootQ] = rootP;
        rank[rootP] += rank[rootQ];
        return true;
    }

private:
    std::vector<int> root;
    std::vector<int> rank;
};

class Solution {
public:
    bool containsCycle(std::vector<std::vector<char>>& grid)
    {
        return approach2(grid);
    }

private:
    bool approach2(const std::vector<std::vector<char>>& grid)
    {
        const int m = grid.size();
        const int n = grid[0].size();
        UnionFind uf(m * n);
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (j + 1 < n && grid[i][j] == grid[i][j + 1] && !uf.connect(encode(i, j, n), encode(i, j + 1, n)))
                    return true;

                if (i + 1 < m && grid[i][j] == grid[i + 1][j] && !uf.connect(encode(i, j, n), encode(i + 1, j, n)))
                    return true;
            }
        }
        return false;
    }

    int encode(int i, int j, int n)
    {
        return i * n + j;
    }

    bool approach1(const std::vector<std::vector<char>>& grid)
    {
        const int m = grid.size();
        const int n = grid[0].size();
        std::vector<std::vector<bool>> visited(m, std::vector<bool>(n, false));
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (!visited[i][j] && dfs(visited, i, j, -1, -1, grid))
                    return true;
            }
        }
        return false;
    }

    bool dfs(std::vector<std::vector<bool>>& visited,
             int i,
             int j,
             int fromX,
             int fromY,
             const std::vector<std::vector<char>>& grid)
    {
        static const std::vector<std::pair<int, int>> kDirections{{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        visited[i][j] = true;
        for (const auto& [dx, dy] : kDirections) {
            const int x = i + dx;
            const int y = j + dy;
            if (x < 0 || x >= grid.size() || y < 0 || y >= grid[0].size() || grid[x][y] != grid[i][j])
                continue;

            if (visited[x][y] && (x != fromX && y != fromY))
                return true;

            if (!visited[x][y] && dfs(visited, x, y, i, j, grid))
                return true;
        }
        return false;
    }
};