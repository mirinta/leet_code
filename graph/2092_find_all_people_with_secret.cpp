#include <map>
#include <unordered_set>
#include <vector>

/**
 * You are given an integer n indicating there are n people numbered from 0 to n - 1. You are also
 * given a 0-indexed 2D integer array meetings where meetings[i] = [xi, yi, timei] indicates that
 * person xi and person yi have a meeting at timei. A person may attend multiple meetings at the
 * same time. Finally, you are given an integer firstPerson.
 *
 * Person 0 has a secret and initially shares the secret with a person firstPerson at time 0. This
 * secret is then shared every time a meeting takes place with a person that has the secret. More
 * formally, for every meeting, if a person xi has the secret at timei, then they will share the
 * secret with person yi, and vice versa.
 *
 * The secrets are shared instantaneously. That is, a person may receive the secret and share it
 * with people in other meetings within the same time frame.
 *
 * Return a list of all the people that have the secret after all the meetings have taken place. You
 * may return the answer in any order.
 *
 * ! 2 <= n <= 10^5
 * ! 1 <= meetings.length <= 10^5
 * ! meetings[i].length == 3
 * ! 0 <= xi, yi <= n - 1
 * ! xi != yi
 * ! 1 <= timei <= 10^5
 * ! 1 <= firstPerson <= n - 1
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
        const int rootP = find(p);
        const int rootQ = find(q);
        if (rootP == rootQ)
            return;

        if (size[rootQ] > size[rootP]) {
            root[rootP] = rootQ;
            size[rootQ] += size[rootP];
        } else {
            root[rootQ] = rootP;
            size[rootP] += size[rootQ];
        }
    }

    void reset(int x)
    {
        root[x] = x;
        size[x] = 1;
    }

private:
    std::vector<int> root;
    std::vector<int> size;
};

class Solution {
public:
    std::vector<int> findAllPeople(int n, std::vector<std::vector<int>>& meetings, int firstPerson)
    {
        std::map<int, std::vector<std::pair<int, int>>> map;
        for (const auto& meeting : meetings) {
            map[meeting[2]].emplace_back(meeting[0], meeting[1]);
        }
        UnionFind uf(n);
        uf.connect(0, firstPerson);
        for (const auto& [time, meetingsAtSameTime] : map) {
            std::unordered_set<int> set;
            for (const auto& [p, q] : meetingsAtSameTime) {
                uf.connect(p, q);
                set.insert(p);
                set.insert(q);
            }
            for (const auto& x : set) {
                if (!uf.isConnected(0, x)) {
                    uf.reset(x);
                }
            }
        }
        std::vector<int> result;
        for (int i = 0; i < n; ++i) {
            if (uf.isConnected(0, i)) {
                result.push_back(i);
            }
        }
        return result;
    }
};