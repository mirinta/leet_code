#include <vector>

/**
 * There are "n" cities. Some of them are connected, while some are not. If city "a" is connected
 * directly with city "b", and city "b" is connected directly with city "c", then city "a" is
 * connected indirectly with city "c".
 *
 * A province is a group of directly or indirectly connected cities and no other cities outside of
 * the group.
 *
 * You are given an "n x n" matrix "isConnected" where isConnected[i][j] = 1 if the ith city and the
 * jth city are directly connected, and isConnected[i][j] otherwise.
 *
 * ! 1 <= n <= 200
 * ! n == isConnected.length
 * ! n == isConnected[i].length
 * ! isConnected[i][j] is 1 or 0.
 * ! isConnected[i][i] == 1
 * ! isConnected[i][j] == isConnected[j][i]
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

    int find(int x)
    {
        if (_root[x] != x) {
            _root[x] = find(_root[x]);
        }
        return _root[x];
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
    std::vector<int> _root;
    std::vector<int> _rank;
    int _count;
};

class Solution {
public:
    int findCircleNum(std::vector<std::vector<int>>& isConnected)
    {
        const int n = isConnected.size();
        UnionFind uf(n);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (isConnected[i][j]) {
                    uf.connect(i, j);
                }
            }
        }
        return uf.count();
    }
};
