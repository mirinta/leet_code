#include <algorithm>
#include <unordered_map>
#include <vector>

/**
 * You are given an integer array nums and an integer target.
 *
 * Return the number of subarrays of nums in which target is the majority element.
 *
 * The majority element of a subarray is the element that appears strictly more than half of the times in that subarray.
 *
 * ! 1 <= nums.length <= 10^5
 * ! 1 <= nums[i] <= 10^9
 * ! 1 <= target <= 10^9
 */

class BinaryIndexedTree {
public:
    explicit BinaryIndexedTree(int n) : tree(n + 1) {}

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
    int lowbit(int i)
    {
        return i & (-i);
    }

    int presum(int i)
    {
        int result = 0;
        for (; i > 0; i -= lowbit(i)) {
            result += tree[i];
        }
        return result;
    }

private:
    std::vector<int> tree;
};

class Solution {
public:
    long long countMajoritySubarrays(std::vector<int>& nums, int target)
    {
        // let flags[i] = 1 if nums[i] == target, -1 otherwise
        // let presum[i] = sum of flags[0:i-1]
        //
        // if nums[j+1:i] is a valid array, then
        // sum of flags[j+1:i] > 0, means presum[i] - presum[j] > 0
        //
        // thus, given index i, we need to count the number of j s.t. presum[j] < presum[i]
        const int n = nums.size();
        std::vector<int> presum(n + 1);
        for (int i = 1; i <= n; ++i) {
            presum[i] = presum[i - 1] + (nums[i - 1] == target ? 1 : -1);
        }
        std::vector<int> copy = presum;
        std::sort(copy.begin(), copy.end());
        copy.erase(std::unique(copy.begin(), copy.end()), copy.end());
        std::unordered_map<long long, int> map;
        for (int i = 0; i < copy.size(); ++i) {
            map[copy[i]] = i;
        }
        BinaryIndexedTree tree(copy.size());
        tree.add(map[0] + 1, 1);
        long long result = 0;
        for (int i = 1; i <= n; ++i) {
            result += tree.query(map[copy.front()] + 1, map[presum[i]]);
            tree.add(map[presum[i]] + 1, 1);
        }
        return result;
    }
};