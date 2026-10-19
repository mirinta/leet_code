#include <numeric>
#include <vector>

/**
 * You are given an array nums of distinct positive integers. You need to sort the array in increasing order based on
 * the sum of the digits of each number. If two numbers have the same digit sum, the smaller number appears first in the
 * sorted order.
 *
 * Return the minimum number of swaps required to rearrange nums into this sorted order.
 *
 * A swap is defined as exchanging the values at two distinct positions in the array.
 *
 * ! 1 <= nums.length <= 10^5
 * ! 1 <= nums[i] <= 10^9
 * ! nums consists of distinct positive integers.
 */

class UnionFind {
public:
    explicit UnionFind(int n) : root(n), size(n, 1), count(n)
    {
        std::iota(root.begin(), root.end(), 0);
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

        if (size[rootQ] > size[rootP]) {
            std::swap(rootP, rootQ);
        }
        root[rootQ] = rootP;
        size[rootP] += size[rootQ];
        count--;
    }

    int numOfConnectedComponents()
    {
        return count;
    }

private:
    std::vector<int> root;
    std::vector<int> size;
    int count;
};

class Solution {
public:
    int minSwaps(std::vector<int>& nums)
    {
        const int n = nums.size();
        std::vector<int> aux(n);
        for (int i = 0; i < n; ++i) {
            aux[i] = helper(nums[i]);
        }
        std::vector<int> indices(n, 0);
        std::iota(indices.begin(), indices.end(), 0);
        std::sort(indices.begin(), indices.end(), [&](const auto& i1, const auto& i2) {
            if (aux[i1] == aux[i2])
                return nums[i1] < nums[i2];

            return aux[i1] < aux[i2];
        });
        UnionFind uf(n);
        for (int i = 0; i < n; ++i) {
            uf.connect(i, indices[i]);
        }
        return n - uf.numOfConnectedComponents();
    }

private:
    int helper(int n)
    {
        int result = 0;
        while (n) {
            result += n % 10;
            n /= 10;
        }
        return result;
    }
};
