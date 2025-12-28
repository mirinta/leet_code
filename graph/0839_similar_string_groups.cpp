#include <string>
#include <vector>

/**
 * Two strings, X and Y, are considered similar if either they are identical or we can make them
 * equivalent by swapping at most two letters (in distinct positions) within the string X.
 *
 * For example, "tars" and "rats" are similar (swapping at positions 0 and 2), and "rats" and "arts"
 * are similar, but "star" is not similar to "tars", "rats", or "arts".
 *
 * Together, these form two connected groups by similarity: {"tars", "rats", "arts"} and {"star"}.
 * Notice that "tars" and "arts" are in the same group even though they are not similar.  Formally,
 * each group is such that a word is in the group if and only if it is similar to at least one other
 * word in the group.
 *
 * We are given a list strs of strings where every string in strs is an anagram of every other
 * string in strs. How many groups are there?
 *
 * ! 1 <= strs.length <= 300
 * ! 1 <= strs[i].length <= 300
 * ! strs[i] consists of lowercase letters only.
 * ! All words in strs have the same length and are anagrams of each other.
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
        if (x != root[x]) {
            root[x] = find(root[x]);
        }
        return root[x];
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
    int numSimilarGroups(std::vector<std::string>& strs)
    {
        const int n = strs.size();
        UnionFind uf(n);
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (isSimilar(strs[i], strs[j])) {
                    uf.connect(i, j);
                }
            }
        }
        return uf.numOfConnectedComponents();
    }

private:
    // assume both s1 and s2 are anagrams of each other
    bool isSimilar(const std::string s1, const std::string& s2)
    {
        int count = 0;
        for (int i = 0; i < s1.size(); ++i) {
            if (s1[i] != s2[i]) {
                count++;
            }
        }
        return count == 0 || count == 2;
    }
};