#include <iostream>
#include <vector>

/**
 * BinaryIndexedTree(LLONG n): n is the num of elements, i.e., n = nums.size()
 *
 * add(LLONG i, LLONG delta): increase nums[i] by delta, i is 1-indexed
 *
 * query(LLONG left, LLONG right): query the sum of nums[left:right], left and right are 1-indexed
 *
 * presum(LLONG i): return the sum of nums[1:i], i is 1-indexed
 *
 * std::vector<LLONG> tree: a 1-indexed array
 */
class BinaryIndexedTree {
    using LLONG = long long;

public:
    explicit BinaryIndexedTree(LLONG n) : tree(n + 1) {}

    void add(LLONG i, LLONG delta)
    {
        for (; i < tree.size(); i += lowbit(i)) {
            tree[i] += delta;
        }
    }

    void reset()
    {
        std::fill(tree.begin(), tree.end(), 0);
    }

    LLONG query(LLONG left, LLONG right)
    {
        return presum(right) - presum(left - 1);
    }

private:
    LLONG lowbit(LLONG i)
    {
        return i & (-i);
    }

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

int main()
{
    // example: query range sum
    std::vector<int> nums{1, 2, 3, 4};
    BinaryIndexedTree tree(nums.size());
    for (int i = 0; i < nums.size(); ++i) {
        tree.add(i + 1, nums[i]);
    }
    std::cout << tree.query(2, 4) << '\n'; // 2+3+4=9
    tree.add(3, 5);                        // nums = [1,2,8,4]
    std::cout << tree.query(2, 4) << '\n'; // 2+8+4=14
    return 0;
}
