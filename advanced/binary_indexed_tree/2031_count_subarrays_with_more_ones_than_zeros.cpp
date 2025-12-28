#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <vector>

/**
 * You are given a binary array nums containing only the integers 0 and 1. Return the number of
 * subarrays in nums that have more 1's than 0's. Since the answer may be very large, return it
 * modulo 10^9 + 7.
 *
 * A subarray is a contiguous sequence of elements within an array.
 *
 * ! 1 <= nums.length <= 10^5
 * ! 0 <= nums[i] <= 1
 */

class BinaryIndexedTree {
public:
    explicit BinaryIndexedTree(int n) : tree(n + 1, 0) {}

    void add(int i, int delta)
    {
        for (; i < tree.size(); i += lowbit(i)) {
            tree[i] += delta;
        }
    }

    int query(int left, int right)
    {
        return presum(right) - presum(left - 1);
    }

private:
    int presum(int i)
    {
        int sum = 0;
        for (; i > 0; i -= lowbit(i)) {
            sum += tree[i];
        }
        return sum;
    }

    int lowbit(int i)
    {
        return i & -i;
    }

private:
    std::vector<int> tree;
};

class Solution {
public:
    int subarraysWithMoreZerosThanOnes(std::vector<int>& nums)
    {
        // diff[i] = 1's - 0's of nums[0:i-1]
        // if nums[j:i+1] is a valid subarray,
        // then diff[i] - diff[j] > 0, j < i
        // given i, we need to count the num of j such that diff[j] < diff[i]
        constexpr int kMod = 1e9 + 7;
        const int n = nums.size();
        std::vector<int> diff(n + 1, 0);
        for (int i = 1; i <= n; ++i) {
            diff[i] = diff[i - 1] + (nums[i - 1] == 1 ? 1 : -1);
        }
        std::unordered_set<int> set(diff.begin(), diff.end());
        std::vector<int> uniques(set.begin(), set.end());
        std::sort(uniques.begin(), uniques.end());
        std::unordered_map<int, int> map;
        for (int i = 0; i < uniques.size(); ++i) {
            map[uniques[i]] = i;
        }
        BinaryIndexedTree tree(uniques.size());
        int result = 0;
        for (int i = 0; i <= n; ++i) {
            result = (result + i - tree.query(map[diff[i]] + 1, map[uniques.back()] + 1)) % kMod;
            tree.add(map[diff[i]] + 1, 1);
        }
        return result;
    }
};