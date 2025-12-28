#include <algorithm>
#include <set>
#include <unordered_map>
#include <vector>

/**
 * You are given a 0-indexed array of positive integers nums and a positive integer limit.
 *
 * In one operation, you can choose any two indices i and j and swap nums[i] and nums[j] if |nums[i]
 * - nums[j]| <= limit.
 *
 * Return the lexicographically smallest array that can be obtained by performing the operation any
 * number of times.
 *
 * An array a is lexicographically smaller than an array b if in the first position where a and b
 * differ, array a has an element that is less than the corresponding element in b. For example, the
 * array [2,10,3] is lexicographically smaller than the array [10,2,3] because they differ at index
 * 0 and 2 < 10.
 *
 * ! 1 <= nums.length <= 10^5
 * ! 1 <= nums[i] <= 10^9
 * ! 1 <= limit <= 10^9
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
    std::vector<int> lexicographicallySmallestArray(std::vector<int>& nums, int limit)
    {
        const int n = nums.size();
        std::vector<std::pair<int, int>> pairs(n);
        for (int i = 0; i < n; ++i) {
            pairs[i] = {nums[i], i};
        }
        std::sort(pairs.begin(), pairs.end(), [](const auto& p1, const auto& p2) { return p1.first < p2.first; });
        UnionFind uf(n);
        for (int i = 1; i < n; ++i) {
            if (pairs[i].first - pairs[i - 1].first <= limit) {
                uf.connect(pairs[i].second, pairs[i - 1].second);
            }
        }
        std::unordered_map<int, std::multiset<int>> map;
        for (int i = 0; i < n; ++i) {
            map[uf.find(i)].insert(nums[i]);
        }
        std::vector<int> result(n);
        for (int i = 0; i < n; ++i) {
            result[i] = *map[uf.find(i)].begin();
            map[uf.find(i)].erase(map[uf.find(i)].begin());
        }
        return result;
    }
};