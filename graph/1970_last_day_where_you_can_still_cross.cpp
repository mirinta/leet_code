#include <vector>

/**
 * There is a 1-based binary matrix where 0 represents land and 1 represents water. You are given
 * integers row and col representing the number of rows and columns in the matrix, respectively.
 *
 * Initially on day 0, the entire matrix is land. However, each day a new cell becomes flooded with
 * water. You are given a 1-based 2D array cells, where cells[i] = [ri, ci] represents that on the
 * ith day, the cell on the ri-th row and ci-th column (1-based coordinates) will be covered with
 * water (i.e., changed to 1).
 *
 * You want to find the last day that it is possible to walk from the top to the bottom by only
 * walking on land cells. You can start from any cell in the top row and end at any cell in the
 * bottom row. You can only travel in the four cardinal directions (left, right, up, and down).
 *
 * Return the last day where it is possible to walk from the top to the bottom by only walking on
 * land cells.
 *
 * ! 2 <= row, col <= 2 * 10^4
 * ! 4 <= row * col <= 2 * 10^4
 * ! cells.length == row * col
 * ! 1 <= ri <= row
 * ! 1 <= ci <= col
 * ! All the values of cells are unique.
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
    int latestDayToCross(int row, int col, std::vector<std::vector<int>>& cells)
    {
        static const std::vector<std::pair<int, int>> kDirections{{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        const int n = row * col;
        const int kVirtualTop = n;
        const int kVirtualBottom = n + 1;
        UnionFind uf(n + 2);
        for (int j = 0; j < col; ++j) {
            uf.connect(kVirtualTop, j);
            uf.connect(kVirtualBottom, (row - 1) * col + j);
        }
        std::vector<std::vector<int>> grid(row, std::vector<int>(col, 0));
        for (const auto& c : cells) {
            grid[c[0] - 1][c[1] - 1] = 1;
        }
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < col; ++j) {
                if (grid[i][j])
                    continue;

                for (const auto& [dx, dy] : kDirections) {
                    const int x = i + dx;
                    const int y = j + dy;
                    if (x < 0 || x >= row || y < 0 || y >= col || grid[x][y])
                        continue;

                    uf.connect(i * col + j, x * col + y);
                }
            }
        }
        for (int t = cells.size() - 1; t >= 0; --t) {
            if (uf.isConnected(kVirtualTop, kVirtualBottom))
                return t + 1;

            const int i = cells[t][0] - 1;
            const int j = cells[t][1] - 1;
            grid[i][j] = 0;
            for (const auto& [dx, dy] : kDirections) {
                const int x = i + dx;
                const int y = j + dy;
                if (x < 0 || x >= row || y < 0 || y >= col || grid[x][y])
                    continue;

                uf.connect(i * col + j, x * col + y);
            }
        }
        return 0;
    }
};