#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <vector>

/**
 * Given an integer array nums, return the number of reverse pairs in the array.
 *
 * A reverse pair is a pair (i, j) where:
 *
 * - 0 <= i < j < nums.length and
 *
 * - nums[i] > 2 * nums[j].
 *
 * ! 1 <= nums.length <= 5 * 10^4
 * ! -2^31 <= nums[i] <= 2^31 - 1
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
    int reversePairs(std::vector<int>& nums)
    {
        return approach1(nums);
    }

private:
    int approach2(const std::vector<int>& nums)
    {
        const int n = nums.size();
        std::unordered_set<long long> set(nums.begin(), nums.end());
        std::vector<long long> uniques(set.begin(), set.end());
        std::sort(uniques.begin(), uniques.end());
        std::unordered_map<long long, int> map;
        for (int i = 0; i < uniques.size(); ++i) {
            map[uniques[i]] = i;
        }
        BinaryIndexedTree tree(uniques.size());
        int result = 0;
        for (int j = 0; j < n; ++j) {
            auto iter = std::upper_bound(uniques.begin(), uniques.end(), 2LL * nums[j]);
            if (iter != uniques.end()) {
                result += tree.query(map[*iter] + 1, map[uniques.back()] + 1);
            }
            tree.add(map[nums[j]] + 1, 1);
        }
        return result;
    }

    int approach1(std::vector<int> nums)
    {
        const int n = nums.size();
        std::vector<int> aux(n);
        int result = 0;
        mergeSort(result, aux, nums, 0, n - 1);
        return result;
    }

    void mergeSort(int& result, std::vector<int>& aux, std::vector<int>& nums, int lo, int hi)
    {
        if (lo >= hi)
            return;

        const int mid = lo + (hi - lo) / 2;
        mergeSort(result, aux, nums, lo, mid);
        mergeSort(result, aux, nums, mid + 1, hi);
        merge(result, aux, nums, lo, mid, hi);
    }

    void merge(int& result, std::vector<int>& aux, std::vector<int>& nums, int lo, int mid, int hi)
    {
        for (int i = lo, j = mid + 1; j <= hi; ++j) {
            while (i <= mid && static_cast<long long>(nums[i]) <= 2 * static_cast<long long>(nums[j])) {
                i++;
            }
            result += mid - i + 1;
        }
        for (int k = lo; k <= hi; ++k) {
            aux[k] = nums[k];
        }
        for (int i = lo, j = mid + 1, k = lo; k <= hi; ++k) {
            if (i == mid + 1 || (j <= hi && aux[j] < aux[i])) {
                nums[k] = aux[j++];
            } else {
                nums[k] = aux[i++];
            }
        }
    }
};