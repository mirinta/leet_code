#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <vector>

/**
 * You are given two 0-indexed integer arrays nums1 and nums2, each of size n, and an integer diff.
 * Find the number of pairs (i, j) such that:
 *
 * - 0 <= i < j <= n - 1 and
 *
 * - nums1[i] - nums1[j] <= nums2[i] - nums2[j] + diff.
 *
 * Return the number of pairs that satisfy the conditions.
 *
 * ! n == nums1.length == nums2.length
 * ! 2 <= n <= 10^5
 * ! -10^4 <= nums1[i], nums2[i] <= 10^4
 * ! -10^4 <= diff <= 10^4
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
    long long numberOfPairs(std::vector<int>& nums1, std::vector<int>& nums2, int diff)
    {
        return approach2(nums1, nums2, diff);
    }

private:
    long long approach2(const std::vector<int>& nums1, const std::vector<int>& nums2, int diff)
    {
        // nums1[i] - nums1[j] <= nums2[i] - nums2[j] + diff
        // nums1[i] - nums2[i] <= nums1[j] - nums2[j] + diff
        // let v[i] = nums1[i] - nums2[i]
        // v[i] <= v[j] + diff, i < j
        const int n = nums1.size();
        std::unordered_set<int> set;
        std::vector<int> v(n);
        for (int i = 0; i < n; ++i) {
            v[i] = nums1[i] - nums2[i];
            set.insert(v[i]);
        }
        std::vector<int> uniques(set.begin(), set.end());
        std::sort(uniques.begin(), uniques.end());
        std::unordered_map<int, int> map;
        for (int i = 0; i < uniques.size(); ++i) {
            map[uniques[i]] = i;
        }
        BinaryIndexedTree tree(uniques.size());
        long long result = 0;
        for (int j = 0; j < n; ++j) {
            auto iter = std::upper_bound(uniques.begin(), uniques.end(), v[j] + diff);
            if (iter != uniques.begin()) {
                result += tree.query(map[uniques.front()] + 1, map[*std::prev(iter)] + 1);
            }
            tree.add(map[v[j]] + 1, 1);
        }
        return result;
    }

    long long approach1(const std::vector<int>& nums1, const std::vector<int>& nums2, int diff)
    {
        const int n = nums1.size();
        std::vector<int> v(n);
        for (int i = 0; i < n; ++i) {
            v[i] = nums1[i] - nums2[i];
        }
        std::vector<int> aux(n);
        long long result = 0;
        mergeSort(result, v, aux, 0, n - 1, diff);
        return result;
    }

    void mergeSort(long long& result, std::vector<int>& nums, std::vector<int>& aux, int lo, int hi, int diff)
    {
        if (lo >= hi)
            return;

        const int mid = lo + (hi - lo) / 2;
        mergeSort(result, nums, aux, lo, mid, diff);
        mergeSort(result, nums, aux, mid + 1, hi, diff);
        merge(result, nums, aux, lo, mid, hi, diff);
    }

    void merge(long long& result, std::vector<int>& nums, std::vector<int>& aux, int lo, int mid, int hi, int diff)
    {
        for (int k = lo; k <= hi; ++k) {
            aux[k] = nums[k];
        }
        for (int i = lo, j = mid + 1; i <= mid; ++i) {
            while (j <= hi && nums[j] < nums[i] - diff) {
                j++;
            }
            result += hi - j + 1;
        }
        for (int i = lo, j = mid + 1, k = lo; k <= hi; ++k) {
            if (i > mid) {
                nums[k] = aux[j++];
                continue;
            }
            if (j > hi) {
                nums[k] = aux[i++];
                continue;
            }
            if (aux[i] > aux[j]) {
                nums[k] = aux[j++];
            } else {
                nums[k] = aux[i++];
            }
        }
    }
};