#include <vector>

class UnionFind {
public:
    explicit UnionFind(int n) : count(n), root(n), size(n, 1)
    {
        for (int i = 0; i < n; ++i) {
            root[i] = i;
        }
    }

    int connectedComponents() const
    {
        return count;
    }

    /**
     * @note x is 0-indexed.
     */
    int find(int x)
    {
        if (x != root[x]) {
            root[x] = find(root[x]);
        }
        return root[x];
    }

    bool connected(int p, int q)
    {
        return find(p) == find(q);
    }

    /**
     * @note p and q are 0-indexed.
     * @note Return false is p and q are already connected.
     */
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

private:
    int count;
    std::vector<int> root;
    std::vector<int> size;
};