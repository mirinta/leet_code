#include <unordered_map>
#include <vector>

/**
 * You are given an integer array nums.
 *
 * A subarray is called balanced if the number of distinct even numbers in the subarray is equal to the number of
 * distinct odd numbers.
 *
 * Return the length of the longest balanced subarray.
 *
 * ! 1 <= nums.length <= 10^5
 * ! 1 <= nums[i] <= 10^5
 */

class SegmentTree {
public:
    explicit SegmentTree(const std::vector<int>& nums) : n(nums.size()), data(4 * n, {0, 0}), lazy(4 * n, 0)
    {
        build(0, n - 1, 1, nums);
    }

    void add(int L, int R, int val)
    {
        add(L, R, 0, n - 1, 1, val);
    }

    int find(int L, int R, int val)
    {
        return find(L, R, 0, n - 1, 1, val);
    }

private:
    int find(int L, int R, int lo, int hi, int id, int val)
    {
        if (hi < L || lo > R)
            return -1;

        if (data[id].first > val || data[id].second < val)
            return -1;

        if (lo == hi)
            return lo;

        spread(id);
        const int mid = lo + (hi - lo) / 2;
        const int index = find(L, R, lo, mid, 2 * id, val);
        if (index < 0)
            return find(L, R, mid + 1, hi, 2 * id + 1, val);

        return index;
    }

    void apply(int id, int val)
    {
        data[id].first += val;
        data[id].second += val;
        lazy[id] += val;
    }

    void spread(int id)
    {
        if (lazy[id] != 0) {
            apply(2 * id, lazy[id]);
            apply(2 * id + 1, lazy[id]);
            lazy[id] = 0;
        }
    }

    void add(int L, int R, int lo, int hi, int id, int val)
    {
        if (lo >= L && hi <= R) {
            apply(id, val);
            return;
        }
        spread(id);
        const int mid = lo + (hi - lo) / 2;
        if (mid >= L) {
            add(L, R, lo, mid, 2 * id, val);
        }
        if (mid < R) {
            add(L, R, mid + 1, hi, 2 * id + 1, val);
        }
        maintain(id);
    }

    void maintain(int id)
    {
        data[id].first = std::min(data[2 * id].first, data[2 * id + 1].first);
        data[id].second = std::max(data[2 * id].second, data[2 * id + 1].second);
    }

    void build(int lo, int hi, int id, const std::vector<int>& nums)
    {
        if (lo == hi) {
            data[id].first = nums[lo];
            data[id].second = nums[lo];
            return;
        }
        const int mid = lo + (hi - lo) / 2;
        build(lo, mid, 2 * id, nums);
        build(mid + 1, hi, 2 * id + 1, nums);
        maintain(id);
    }

private:
    const int n;
    std::vector<std::pair<int, int>> data; // <min, max>
    std::vector<int> lazy;
};

class Solution {
public:
    int longestBalanced(std::vector<int>& nums)
    {
        const int n = nums.size();
        SegmentTree tree(std::vector<int>(n + 1, 0));
        std::unordered_map<int, int> map; // last appearance of nums[i]
        int result = 0;
        for (int i = 1, sum = 0; i <= n; ++i) {
            const auto& curr = nums[i - 1];
            const int flag = (curr % 2) ? 1 : -1;
            if (map.count(curr)) {
                tree.add(map[curr], i - 1, -flag);
            } else {
                sum += flag;
                tree.add(i, n, flag);
            }
            map[curr] = i;
            if (const int j = tree.find(0, i - 1, sum); j >= 0) {
                result = std::max(result, i - j);
            }
        }
        return result;
    }
};