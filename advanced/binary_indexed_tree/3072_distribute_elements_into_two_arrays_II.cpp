#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <vector>

/**
 * You are given a 1-indexed array of integers nums of length n.
 *
 * We define a function greaterCount such that greaterCount(arr, val) returns the number of elements
 * in arr that are strictly greater than val.
 *
 * You need to distribute all the elements of nums between two arrays arr1 and arr2 using n
 * operations. In the first operation, append nums[1] to arr1. In the second operation, append
 * nums[2] to arr2. Afterwards, in the ith operation:
 *
 * - If greaterCount(arr1, nums[i]) > greaterCount(arr2, nums[i]), append nums[i] to arr1.
 *
 * - If greaterCount(arr1, nums[i]) < greaterCount(arr2, nums[i]), append nums[i] to arr2.
 *
 * - If greaterCount(arr1, nums[i]) == greaterCount(arr2, nums[i]), append nums[i] to the array with
 * a lesser number of elements.
 *
 * - If there is still a tie, append nums[i] to arr1.
 *
 * The array result is formed by concatenating the arrays arr1 and arr2. For example, if arr1 ==
 * [1,2,3] and arr2 == [4,5,6], then result = [1,2,3,4,5,6].
 *
 * Return the integer array result.
 *
 * ! 3 <= n <= 10^5
 * ! 1 <= nums[i] <= 10^9
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
    std::vector<int> resultArray(std::vector<int>& nums)
    {
        auto unique = nums;
        std::sort(unique.begin(), unique.end());
        auto iter = std::unique(unique.begin(), unique.end());
        unique.erase(iter, unique.end());
        std::unordered_map<int, int> map;
        for (int i = 0; i < unique.size(); ++i) {
            map[unique[i]] = i;
        }
        std::vector<int> nums1{nums[0]};
        BinaryIndexedTree tree1(unique.size());
        tree1.add(map[nums[0]] + 1, 1);
        std::vector<int> nums2{nums[1]};
        BinaryIndexedTree tree2(unique.size());
        tree2.add(map[nums[1]] + 1, 1);
        for (int i = 2; i < nums.size(); ++i) {
            const int count1 = nums1.size() - tree1.query(1, map[nums[i]] + 1);
            const int count2 = nums2.size() - tree2.query(1, map[nums[i]] + 1);
            if (count1 < count2 || (count1 == count2 && nums2.size() < nums1.size())) {
                nums2.push_back(nums[i]);
                tree2.add(map[nums[i]] + 1, 1);
            } else {
                nums1.push_back(nums[i]);
                tree1.add(map[nums[i]] + 1, 1);
            }
        }
        nums1.insert(nums1.end(), nums2.begin(), nums2.end());
        return nums1;
    }
};