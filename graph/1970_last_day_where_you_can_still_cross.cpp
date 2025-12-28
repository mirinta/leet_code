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
    explicit UnionFind(int n) : _root(n), _rank(n), _count(n)
    {
        for (int i = 0; i < n; ++i) {
            _root[i] = i;
            _rank[i] = 1;
        }
    }

    int count() const
    {
        return _count;
    }

    int find(int x) const
    {
        if (x != _root[x]) {
            _root[x] = find(_root[x]);
        }
        return _root[x];
    }

    bool isConnected(int p, int q) const
    {
        return find(p) == find(q);
    }

    void connect(int p, int q)
    {
        const int rootP = find(p);
        const int rootQ = find(q);
        if (rootP == rootQ)
            return;

        if (_rank[rootP] > _rank[rootQ]) {
            _root[rootQ] = rootP;
        } else if (_rank[rootP] < _rank[rootQ]) {
            _root[rootP] = rootQ;
        } else {
            _root[rootQ] = rootP;
            _rank[rootP] += 1;
        }
        _count -= 1;
    }

private:
    mutable std::vector<int> _root;
    std::vector<int> _rank;
    int _count;
};

class Solution {
public:
    int latestDayToCross(int row, int col, std::vector<std::vector<int>>& cells)
    {
        const int numOfNodes = row * col + 2; // two extra nodes: virtual top and virtual bottom
        UnionFind uf(numOfNodes);
        const int kVirtualTop = numOfNodes - 2;
        const int kVirtualBottom = numOfNodes - 1;
        std::vector<std::vector<int>> graph(row, std::vector<int>(col, 0)); // initialize with 0, all lands
        // connect each node in the top row with the virtual top node, and
        // connect each node in the bottom row with the virtual bottom node
        for (int j = 0; j < col; ++j) {
            uf.connect(j, kVirtualTop);
            uf.connect((row - 1) * col + j, kVirtualBottom);
        }
        // get the final graph
        for (const auto& cell : cells) {
            const int i = cell[0] - 1; // cell is 1-indexed
            const int j = cell[1] - 1; // cell is 1-indexed
            graph[i][j] = 1;
        }
        // connect lands
        const std::vector<std::pair<int, int>> kDirections{{0, -1}, {0, 1}, {1, 0}, {-1, 0}};
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < col; ++j) {
                if (graph[i][j] == 1)
                    continue;

                for (const auto& [dx, dy] : kDirections) {
                    const int x = i + dx;
                    const int y = j + dy;
                    if (x < 0 || x >= row || y < 0 || y >= col || graph[x][y] == 1)
                        continue;

                    uf.connect(i * col + j, x * col + y);
                }
            }
        }
        // check cells in reverse order, reset cells[i] from 1 to 0
        for (int t = cells.size() - 1; t >= 0; --t) {
            if (uf.isConnected(kVirtualTop, kVirtualBottom))
                return t + 1; // t is 0-indexed, we want 1-indexed

            const int i = cells[t][0] - 1;
            const int j = cells[t][1] - 1;
            graph[i][j] = 0;
            for (const auto& [dx, dy] : kDirections) {
                const int x = i + dx;
                const int y = j + dy;
                if (x < 0 || x >= row || y < 0 || y >= col || graph[x][y] == 1)
                    continue;

                uf.connect(i * col + j, x * col + y);
            }
        }
        return 0;
    }
};