#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <vector>

/**
 * Given two integer arrays nums1 and nums2 of length n, count the pairs of indices (i, j) such that
 * i < j and nums1[i] + nums1[j] > nums2[i] + nums2[j].
 *
 * Return the number of pairs satisfying the condition.
 *
 * ! n == nums1.length == nums2.length
 * ! 1 <= n <= 10^5
 * ! 1 <= nums1[i], nums2[i] <= 10^5
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

    long long query(int left, int right)
    {
        return prefix(right) - prefix(left - 1);
    }

private:
    int lowbit(int i)
    {
        return i & (-i);
    }

    long long prefix(int i)
    {
        long long result = 0;
        for (; i > 0; i -= lowbit(i)) {
            result += tree[i];
        }
        return result;
    }

private:
    std::vector<long long> tree;
};

class Solution {
public:
    long long countPairs(std::vector<int>& nums1, std::vector<int>& nums2)
    {
        return approach2(nums1, nums2);
    }

private:
    long long approach2(const std::vector<int>& nums1, const std::vector<int>& nums2)
    {
        // let nums[i] = nums1[i] - nums2[i]
        // then we need to count the pair of indices (i, j) such that
        // i < j and nums[i] + nums[j] > 0
        const int n = nums1.size();
        std::vector<int> nums(n);
        for (int i = 0; i < n; ++i) {
            nums[i] = nums1[i] - nums2[i];
        }
        std::sort(nums.begin(), nums.end());
        long long result = 0;
        for (int i = 0; i < n; ++i) {
            auto iter = std::upper_bound(nums.begin(), nums.begin() + i, -nums[i]);
            result += i - (iter - nums.begin());
        }
        return result;
    }

    long long approach1(const std::vector<int>& nums1, const std::vector<int>& nums2)
    {
        const int n = nums1.size();
        std::vector<int> nums(n);
        for (int i = 0; i < n; ++i) {
            nums[i] = nums1[i] - nums2[i];
        }
        std::unordered_set<int> set(nums.begin(), nums.end());
        std::vector<int> unique(set.begin(), set.end());
        const int m = unique.size();
        std::sort(unique.begin(), unique.end());
        std::unordered_map<int, int> map;
        for (int i = 0; i < m; ++i) {
            map[unique[i]] = i;
        }
        BinaryIndexedTree tree(m);
        long long result = 0;
        for (int i = 0; i < n; ++i) {
            auto iter = std::upper_bound(unique.begin(), unique.end(), -nums[i]);
            if (iter != unique.end()) {
                result += tree.query(map[*iter] + 1, m);
            }
            tree.add(map[nums[i]] + 1, 1);
        }
        return result;
    }
};