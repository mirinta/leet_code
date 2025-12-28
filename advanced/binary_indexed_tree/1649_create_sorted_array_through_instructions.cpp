#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <vector>

/**
 * Given an integer array instructions, you are asked to create a sorted array from the elements in
 * instructions. You start with an empty container nums. For each element from left to right in
 * instructions, insert it into nums. The cost of each insertion is the minimum of the following:
 *
 * - The number of elements currently in nums that are strictly less than instructions[i].
 *
 * - The number of elements currently in nums that are strictly greater than instructions[i].
 *
 * For example, if inserting element 3 into nums = [1,2,3,5], the cost of insertion is min(2, 1)
 * (elements 1 and 2 are less than 3, element 5 is greater than 3) and nums will become [1,2,3,3,5].
 *
 * Return the total cost to insert all elements from instructions into nums. Since the answer may be
 * large, return it modulo 10^9 + 7.
 *
 * ! 1 <= instructions.length <= 10^5
 * ! 1 <= instructions[i] <= 10^5
 */

class BinaryIndexedTree {
public:
    explicit BinaryIndexedTree(int n) : tree(n + 1, 0) {}

    void add(int i, long long delta)
    {
        if (!validate(i))
            return;

        while (i < tree.size()) {
            tree[i] += delta;
            i += lowbit(i);
        }
    }

    long long query(int left, int right)
    {
        if (left > right || !validate(left) || !validate(right))
            return 0;

        return presum(right) - presum(left - 1);
    }

private:
    int lowbit(int i)
    {
        return i & (-i);
    }

    bool validate(int i) const
    {
        return i >= 1 && i < tree.size();
    }

    long long presum(int i)
    {
        long long sum = 0;
        while (i > 0) {
            sum += tree[i];
            i -= lowbit(i);
        }
        return sum;
    }

private:
    std::vector<long long> tree;
};

class Solution {
public:
    int createSortedArray(std::vector<int>& instructions)
    {
        constexpr int kMod = 1e9 + 7;
        auto unique = instructions;
        std::sort(unique.begin(), unique.end());
        unique.erase(std::unique(unique.begin(), unique.end()), unique.end());
        std::unordered_map<int, int> map;
        for (int i = 0; i < unique.size(); ++i) {
            map[unique[i]] = i;
        }
        BinaryIndexedTree tree(unique.size());
        int result = 0;
        for (int i = 0; i < instructions.size(); ++i) {
            const auto& val = instructions[i];
            const int less = i - tree.query(map[val] + 1, unique.size());
            const int greater = i - tree.query(1, map[val] + 1);
            result = (result + std::min(less, greater)) % kMod;
            tree.add(map[val] + 1, 1);
        }
        return result;
    }
};