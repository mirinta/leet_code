#include <vector>

/**
 * Given an integer array nums, handle multiple queries of the following types:
 *
 * 1. Update the value of an element in nums.
 *
 * 2. Calculate the sum of the elements of nums between indices left and right inclusive where left
 * <= right.
 *
 * Implement the NumArray class:
 *
 * - NumArray(int[] nums) Initializes the object with the integer array nums.
 *
 * - void update(int index, int val) Updates the value of nums[index] to be val.
 *
 * - int sumRange(int left, int right) Returns the sum of the elements of nums between indices left
 * and right inclusive (i.e. nums[left] + nums[left + 1] + ... + nums[right]).
 *
 * ! 1 <= nums.length <= 3 * 10^4
 * ! -100 <= nums[i] <= 100
 * ! 0 <= index < nums.length
 * ! -100 <= val <= 100
 * ! 0 <= left <= right < nums.length
 * ! At most 3 * 104 calls will be made to update and sumRange.
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

class NumArray {
public:
    NumArray(std::vector<int>& nums) : tree(nums.size())
    {
        for (int i = 0; i < nums.size(); ++i) {
            tree.add(i + 1, nums[i]);
        }
    }

    void update(int index, int val)
    {
        const int oldVal = tree.query(index + 1, index + 1);
        tree.add(index + 1, val - oldVal);
    }

    int sumRange(int left, int right)
    {
        return tree.query(left + 1, right + 1);
    }

private:
    BinaryIndexedTree tree;
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * obj->update(index,val);
 * int param_2 = obj->sumRange(left,right);
 */

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * obj->update(index,val);
 * int param_2 = obj->sumRange(left,right);
 */
