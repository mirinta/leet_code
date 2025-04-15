#include <unordered_map>
#include <vector>

/**
 * You are given two 0-indexed arrays nums1 and nums2 of length n, both of which are permutations of
 * [0, 1, ..., n - 1].
 *
 * A good triplet is a set of 3 distinct values which are present in increasing order by position
 * both in nums1 and nums2. In other words, if we consider pos1v as the index of the value v in
 * nums1 and pos2v as the index of the value v in nums2, then a good triplet will be a set (x, y, z)
 * where 0 <= x, y, z <= n - 1, such that pos1x < pos1y < pos1z and pos2x < pos2y < pos2z.
 *
 * Return the total number of good triplets.
 *
 * ! n == nums1.length == nums2.length
 * ! 3 <= n <= 10^5
 * ! 0 <= nums1[i], nums2[i] <= n - 1
 * ! nums1 and nums2 are permutations of [0, 1, ..., n - 1].
 */

class BinaryIndexedTree
{
    using LLONG = long long;

public:
    explicit BinaryIndexedTree(LLONG n) : tree(n + 1) {}

    void add(LLONG i, LLONG delta)
    {
        for (; i < tree.size(); i += lowbit(i)) {
            tree[i] += delta;
        }
    }

    void reset() { std::fill(tree.begin(), tree.end(), 0); }

    LLONG query(LLONG left, LLONG right) { return presum(right) - presum(left - 1); }

private:
    LLONG lowbit(LLONG i) { return i & (-i); }

    LLONG presum(LLONG i)
    {
        LLONG sum = 0;
        for (; i > 0; i -= lowbit(i)) {
            sum += tree[i];
        }
        return sum;
    }

private:
    std::vector<LLONG> tree;
};

class Solution
{
public:
    long long goodTriplets(std::vector<int>& nums1, std::vector<int>& nums2)
    {
        const int n = nums1.size();
        std::unordered_map<int, int> map;
        for (int i = 0; i < n; ++i) {
            map[nums2[i]] = i;
        }
        std::vector<int> info(n);
        for (int i = 0; i < n; ++i) {
            info[i] = map[nums1[i]];
        }
        BinaryIndexedTree tree1(n);
        BinaryIndexedTree tree2(n);
        for (const auto& val : info) {
            tree2.add(val + 1, 1);
        }
        long long result = 0;
        for (int j = 0; j < n; ++j) {
            tree2.add(info[j] + 1, -1);
            const auto count1 = tree1.query(1, info[j]);
            const auto count2 = tree2.query(info[j] + 2, n);
            result += count1 * count2;
            tree1.add(info[j] + 1, 1);
        }
        return result;
    }
};
