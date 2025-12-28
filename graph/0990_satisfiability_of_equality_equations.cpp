#include <string>
#include <vector>

/**
 * You are given an array of strings "equations" that represent relationships between variables
 * where each string equation[i] is o length 4 and takes one of two different forms: "xi == yi" or
 * "xi != yi". Here, xi and yi are lowercase letters (not necessarily different) that represent
 * one-letter variable names.
 *
 * Return "true" if it is possible to assign integers to variable names so as to satisfy all the
 * given equations, or false otherwise.
 *
 * ! 1 <= equations.length <= 500
 * ! equations[i].length == 4
 * ! equations[i][0] is a lowercase letter.
 * ! equations[i][1] is either '=' or '!'.
 * ! equations[i][2] is '='.
 * ! equations[i][3] is a lowercase letter.
 */

class UnionFind {
public:
    explicit UnionFind(int n) : count(n), root(n), rank(n)
    {
        for (int i = 0; i < n; ++i) {
            root[i] = i;
            rank[i] = 1;
        }
    }

    int numOfConnectedComponents() const
    {
        return count;
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
        const int rootP = find(p);
        const int rootQ = find(q);
        if (rootP == rootQ)
            return;

        if (rank[rootP] > rank[rootQ]) {
            root[rootQ] = rootP;
        } else if (rank[rootP] < rank[rootQ]) {
            root[rootP] = rootQ;
        } else {
            root[rootQ] = rootP;
            rank[rootP]++;
        }
        count--;
    }

private:
    int count;
    std::vector<int> root;
    std::vector<int> rank;
};

class Solution {
public:
    bool equationsPossible(std::vector<std::string>& equations)
    {
        // variables are lowercase letters
        UnionFind uf(26);
        for (const auto& equation : equations) {
            if (equation[1] == '=') {
                uf.connect(equation[0] - 'a', equation[3] - 'a');
            }
        }
        for (const auto& equation : equations) {
            if (equation[1] == '!' && uf.isConnected(equation[0] - 'a', equation[3] - 'a'))
                return false;
        }
        return true;
    }
};
