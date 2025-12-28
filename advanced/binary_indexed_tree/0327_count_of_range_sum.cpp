#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <vector>

/**
 * Given an integer array nums and two integers lower and upper, return the number of range sums
 * that lie in [lower, upper] inclusive.
 *
 * Range sum S(i, j) is defined as the sum of the elements in nums between indices i and j
 * inclusive, where i <= j.
 *
 * ! 1 <= nums.length <= 10^5
 * ! -2^31 <= nums[i] <= 2^31 - 1
 * ! -10^5 <= lower <= upper <= 10^5
 * ! The answer is guaranteed to fit in a 32-bit integer.
 */

class BinaryIndexedTree {
public:
    explicit BinaryIndexedTree(int n) : tree(n + 1, 0) {};

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
    int countRangeSum(std::vector<int>& nums, int lower, int upper)
    {
        return approach1(nums, lower, upper);
    }

private:
    int approach2(const std::vector<int>& nums, int lower, int upper)
    {
        // if nums[i+1:j] is a valid subarray, i<j
        // then lower <= sum of nums[i+1:j] <= upper
        // let presum[i] = sum of nums[0:i]
        // lower <= presum[j] - presum[i] <= upper
        // given index j, we need to count the num of index i
        // such that i < j and presum[j] - upper <= presum[i] <= presum[j] - lower
        const int n = nums.size();
        std::vector<long long> presum(n + 1, 0);
        for (int i = 1; i <= n; ++i) {
            presum[i] = presum[i - 1] + nums[i - 1];
        }
        std::unordered_set<long long> set(presum.begin(), presum.end());
        std::vector<long long> uniques(set.begin(), set.end());
        std::sort(uniques.begin(), uniques.end());
        BinaryIndexedTree tree(uniques.size());
        std::unordered_map<long long, int> map;
        for (int i = 0; i < uniques.size(); ++i) {
            map[uniques[i]] = i;
        }
        int result = 0;
        for (int j = 0; j <= n; ++j) {
            auto iter1 = std::lower_bound(uniques.begin(), uniques.end(), presum[j] - upper);
            auto iter2 = std::upper_bound(uniques.begin(), uniques.end(), presum[j] - lower);
            if (iter1 != uniques.end() && iter2 != uniques.begin()) {
                result += tree.query(map[*iter1] + 1, map[*std::prev(iter2)] + 1);
                ;
            }
            tree.add(map[presum[j]] + 1, 1);
        }
        return result;
    }

    int approach1(const std::vector<int>& nums, int lower, int upper)
    {
        const int n = nums.size();
        std::vector<long long> presum(n + 1, 0);
        for (int i = 1; i <= n; ++i) {
            presum[i] = presum[i - 1] + nums[i - 1];
        }
        std::vector<long long> aux(n + 1);
        int result = 0;
        mergeSort(result, presum, aux, 0, n, lower, upper);
        return result;
    }

    void mergeSort(int& result,
                   std::vector<long long>& nums,
                   std::vector<long long>& aux,
                   int lo,
                   int hi,
                   int lower,
                   int upper)
    {
        if (lo >= hi)
            return;

        const int mid = lo + (hi - lo) / 2;
        mergeSort(result, nums, aux, lo, mid, lower, upper);
        mergeSort(result, nums, aux, mid + 1, hi, lower, upper);
        merge(result, nums, aux, lo, mid, hi, lower, upper);
    }

    void merge(int& result,
               std::vector<long long>& nums,
               std::vector<long long>& aux,
               int lo,
               int mid,
               int hi,
               int lower,
               int upper)
    {
        for (int k = lo; k <= hi; ++k) {
            aux[k] = nums[k];
        }
        // count elements using sliding window or binary search
        for (int j = mid + 1, start = lo, end = lo; j <= hi; ++j) {
            while (start <= mid && nums[start] < nums[j] - upper) {
                start++;
            }
            while (end <= mid && nums[end] <= nums[j] - lower) {
                end++;
            }
            result += end - start;
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