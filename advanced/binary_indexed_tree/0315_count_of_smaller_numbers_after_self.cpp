#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <vector>

/**
 * Given an integer array nums, return an integer array counts where counts[i] is the number of
 * smaller elements to the right of nums[i].
 *
 * ! 1 <= nums.length <= 10^5
 * ! -10^4 <= nums[i] <= 10^4
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
    std::vector<int> countSmaller(std::vector<int>& nums)
    {
        return approach2(nums);
    }

private:
    std::vector<int> approach2(const std::vector<int>& nums)
    {
        const int n = nums.size();
        std::unordered_set<int> set(nums.begin(), nums.end());
        std::vector<int> v(set.begin(), set.end());
        std::sort(v.begin(), v.end());
        const int m = v.size();
        std::unordered_map<int, int> map;
        for (int i = 0; i < m; ++i) {
            map[v[i]] = i;
        }
        BinaryIndexedTree tree(m);
        std::vector<int> result(n, 0);
        for (int i = n - 1; i >= 0; --i) {
            result[i] = (n - i - 1) - tree.query(map[nums[i]] + 1, map[v.back()] + 1);
            tree.add(map[nums[i]] + 1, 1);
        }
        return result;
    }

    std::vector<int> approach1(std::vector<int>& nums)
    {
        const int n = nums.size();
        std::vector<std::pair<int, int>> v(n); // <nums[i], i>
        for (int i = 0; i < n; ++i) {
            v[i].first = nums[i];
            v[i].second = i;
        }
        std::vector<std::pair<int, int>> aux(n);
        std::vector<int> result(n);
        mergeSort(result, aux, v, 0, n - 1);
        return result;
    }

    void mergeSort(std::vector<int>& result,
                   std::vector<std::pair<int, int>>& aux,
                   std::vector<std::pair<int, int>>& v,
                   int lo,
                   int hi)
    {
        if (lo >= hi)
            return;

        const int mid = lo + (hi - lo) / 2;
        mergeSort(result, aux, v, lo, mid);
        mergeSort(result, aux, v, mid + 1, hi);
        merge(result, aux, v, lo, mid, hi);
    }

    void merge(std::vector<int>& result,
               std::vector<std::pair<int, int>>& aux,
               std::vector<std::pair<int, int>>& v,
               int lo,
               int mid,
               int hi)
    {
        // lo ... mid mid+1 ... right
        // |<-LEFT->| |<---RIGHT--->|
        for (int k = lo; k <= hi; ++k) {
            aux[k] = v[k];
        }
        for (int i = mid, j = hi; i >= lo; --i) {
            while (j >= mid + 1 && v[j].first >= v[i].first) {
                j--;
            }
            result[v[i].second] += j - mid;
        }
        for (int i = lo, j = mid + 1, k = lo; k <= hi; ++k) {
            if (i > mid || (j <= hi && aux[i].first > aux[j].first)) {
                v[k] = aux[j++];
            } else {
                v[k] = aux[i++];
            }
        }
    }
};