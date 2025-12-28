#include <algorithm>
#include <unordered_map>
#include <vector>

/**
 * You are given an integer array of unique positive integers nums. Consider the following graph:
 *
 * - There are nums.length nodes, labeled nums[0] to nums[nums.length - 1],
 *
 * - There is an undirected edge between nums[i] and nums[j] if nums[i] and nums[j] share a common
 * factor greater than 1.
 *
 * Return the size of the largest connected component in the graph.
 *
 * ! 1 <= nums.length <= 2 * 10^4
 * ! 1 <= nums[i] <= 10^5
 * ! All the values of nums are unique.
 */

class UnionFind {
public:
    explicit UnionFind(int n) : root(n), rank(n, 1)
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

    void connect(int p, int q)
    {
        int rootP = find(p);
        int rootQ = find(q);
        if (rootP == rootQ)
            return;

        if (rank[rootP] < rank[rootQ]) {
            std::swap(rootP, rootQ);
        }
        root[rootQ] = rootP;
        rank[rootP] += rank[rootQ];
    }

private:
    std::vector<int> root;
    std::vector<int> rank;
};

class Solution {
public:
    int largestComponentSize(std::vector<int>& nums)
    {
        UnionFind uf(*std::max_element(nums.begin(), nums.end()) + 1);
        for (const auto& val : nums) {
            for (const auto& f : getPrimeFactors(val)) {
                uf.connect(val, f);
            }
        }
        int result = 0;
        std::unordered_map<int, int> count;
        for (const auto& val : nums) {
            count[uf.find(val)]++;
            result = std::max(result, count[uf.find(val)]);
        }
        return result;
    }

private:
    std::vector<int> getPrimeFactors(int n)
    {
        std::vector<int> result;
        for (int i = 2; i * i <= n; ++i) {
            if (n % i == 0) {
                result.push_back(i);
                while (n % i == 0) {
                    n /= i;
                }
            }
        }
        if (n != 1) {
            result.push_back(n);
        }
        return result;
    }
};
