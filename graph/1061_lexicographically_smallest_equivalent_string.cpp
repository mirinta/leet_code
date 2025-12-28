#include <string>
#include <vector>

/**
 * You are given two strings of the same length s1 and s2 and a string baseStr.
 *
 * We say s1[i] and s2[i] are equivalent characters.
 *
 * - For example, if s1 = "abc" and s2 = "cde", then we have 'a' == 'c', 'b' == 'd', and 'c' == 'e'.
 *
 * Equivalent characters follow the usual rules of any equivalence relation:
 *
 * - Reflexivity: 'a' == 'a'.
 *
 * - Symmetry: 'a' == 'b' implies 'b' == 'a'.
 *
 * - Transitivity: 'a' == 'b' and 'b' == 'c' implies 'a' == 'c'.
 *
 * For example, given the equivalency information from s1 = "abc" and s2 = "cde", "acd" and "aab"
 * are equivalent strings of baseStr = "eed", and "aab" is the lexicographically smallest equivalent
 * string of baseStr.
 *
 * Return the lexicographically smallest equivalent string of baseStr by using the equivalency
 * information from s1 and s2.
 *
 * ! 1 <= s1.length, s2.length, baseStr <= 1000
 * ! s1.length == s2.length
 * ! s1, s2, and baseStr consist of lowercase English letters.
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
    std::string smallestEquivalentString(std::string s1, std::string s2, std::string baseStr)
    {
        UnionFind uf(26);
        for (int i = 0; i < s1.size(); ++i) {
            uf.connect(s1[i] - 'a', s2[i] - 'a');
        }
        std::string result(std::move(baseStr));
        for (auto& c : result) {
            for (int i = 0; i < 26; ++i) {
                if (uf.isConnected(c - 'a', i)) {
                    c = i + 'a';
                    break;
                }
            }
        }
        return result;
    }
};
