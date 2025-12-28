#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

/**
 * You are given a string s, and an array of pairs of indices in the string pairs where pairs[i] =
 * [a, b] indicates 2 indices(0-indexed) of the string.
 *
 * You can swap the characters at any pair of indices in the given pairs any number of times.
 *
 * Return the lexicographically smallest string that s can be changed to after using the swaps.
 *
 * ! 1 <= s.length <= 10^5
 * ! 0 <= pairs.length <= 10^5
 * ! 0 <= pairs[i][0], pairs[i][1] < s.length
 * ! s only contains lower case English letters.
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
        if (x != _root[x]) {
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
    std::string smallestStringWithSwaps(std::string& s, std::vector<std::vector<int>>& pairs)
    {
        // s = "dcab", pairs = [[0,3],[1,2],[0,2]]
        // - [0,3,2] are connected
        // - since we can swap infinite times, s[0] can be changed to either s[3] or s[2]
        // - then s[0] = min(s[0], s[3], s[2]), s[2] is the second minimum, and so on
        UnionFind uf(s.size());
        for (const auto& pair : pairs) {
            uf.connect(pair[0], pair[1]);
        }
        std::unordered_map<int, std::priority_queue<char, std::vector<char>, std::greater<>>> map;
        for (int i = 0; i < s.size(); ++i) {
            map[uf.find(i)].push(s[i]);
        }
        std::string result(s);
        for (int i = 0; i < s.size(); ++i) {
            const int root = uf.find(i);
            result[i] = map[root].top();
            map[root].pop();
        }
        return result;
    }
};
