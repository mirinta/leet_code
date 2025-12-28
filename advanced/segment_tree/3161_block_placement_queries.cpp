#include <set>
#include <vector>

/**
 * There exists an infinite number line, with its origin at 0 and extending towards the positive
 * x-axis.
 *
 * You are given a 2D array queries, which contains two types of queries:
 *
 * 1. For a query of type 1, queries[i] = [1, x]. Build an obstacle at distance x from the origin.
 * It is guaranteed that there is no obstacle at distance x when the query is asked.
 *
 * 2. For a query of type 2, queries[i] = [2, x, sz]. Check if it is possible to place a block of
 * size sz anywhere in the range [0, x] on the line, such that the block entirely lies in the range
 * [0, x]. A block cannot be placed if it intersects with any obstacle, but it may touch it. Note
 * that you do not actually place the block. Queries are separate.
 *
 * Return a boolean array results, where results[i] is true if you can place the block specified in
 * the ith query of type 2, and false otherwise.
 *
 * ! 1 <= queries.length <= 15 * 10^4
 * ! 2 <= queries[i].length <= 3
 * ! 1 <= queries[i][0] <= 2
 * ! 1 <= x, sz <= min(5 * 10^4, 3 * queries.length)
 * ! The input is generated such that for queries of type 1, no obstacle exists at distance x when
 * ! the query is asked.
 * ! The input is generated such that there is at least one query of type 2.
 */

class SegmentTree {
public:
    explicit SegmentTree(const std::vector<int>& nums)
        : n(nums.size()), data(4 * n, 0), lazy(4 * n, 0), flag(4 * n, false)
    {
        build(0, n - 1, 1, nums);
    }

    int query(int L, int R)
    {
        return query(L, R, 0, n - 1, 1);
    }

    void set(int L, int R, int val)
    {
        set(L, R, val, 0, n - 1, 1);
    }

private:
    void build(int lo, int hi, int id, const std::vector<int>& nums)
    {
        if (lo == hi) {
            data[id] = nums[lo];
            return;
        }
        const int mid = lo + (hi - lo) / 2;
        build(lo, mid, 2 * id, nums);
        build(mid + 1, hi, 2 * id + 1, nums);
        data[id] = std::max(data[2 * id], data[2 * id + 1]);
    }

    int query(int L, int R, int lo, int hi, int id)
    {
        if (lo >= L && hi <= R)
            return data[id];

        if (flag[id]) {
            data[2 * id] = lazy[id];
            data[2 * id + 1] = lazy[id];
            lazy[2 * id] = lazy[id];
            lazy[2 * id + 1] = lazy[id];
            lazy[id] = 0;
            flag[2 * id] = true;
            flag[2 * id + 1] = true;
            flag[id] = false;
        }
        const int mid = lo + (hi - lo) / 2;
        int result = INT_MIN;
        if (mid >= L) {
            result = std::max(result, query(L, R, lo, mid, 2 * id));
        }
        if (mid < R) {
            result = std::max(result, query(L, R, mid + 1, hi, 2 * id + 1));
        }
        return result;
    }

    void set(int L, int R, int val, int lo, int hi, int id)
    {
        if (lo >= L && hi <= R) {
            data[id] = val;
            lazy[id] = val;
            flag[id] = true;
            return;
        }
        if (flag[id]) {
            data[2 * id] = lazy[id];
            data[2 * id + 1] = lazy[id];
            lazy[2 * id] = lazy[id];
            lazy[2 * id + 1] = lazy[id];
            lazy[id] = 0;
            flag[2 * id] = true;
            flag[2 * id + 1] = true;
            flag[id] = false;
        }
        const int mid = lo + (hi - lo) / 2;
        if (mid >= L) {
            set(L, R, val, lo, mid, 2 * id);
        }
        if (mid < R) {
            set(L, R, val, mid + 1, hi, 2 * id + 1);
        }
        data[id] = std::max(data[2 * id], data[2 * id + 1]);
    }

private:
    const int n;
    std::vector<int> data;  // 1-indexed
    std::vector<int> lazy;  // 1-indexed
    std::vector<bool> flag; // 1-indexed
};

class Solution {
public:
    std::vector<bool> getResults(std::vector<std::vector<int>>& queries)
    {
        int max = 0;
        for (const auto& q : queries) {
            max = std::max(max, q[1]);
        }
        // tree[i] = empty space between i and the nearest block to the left of i
        SegmentTree tree(std::vector<int>(max + 2, 0));
        std::set<int> set{0, max + 1};
        std::vector<bool> result;
        for (const auto& q : queries) {
            const int x = q[1];
            auto iter = set.lower_bound(x);
            const int prev = *std::prev(iter);
            const int next = *iter;
            if (q[0] == 1) {
                set.insert(x);
                tree.set(x, x, x - prev);
                tree.set(next, next, next - x);
            } else {
                result.push_back(std::max(x - prev, tree.query(0, prev)) >= q[2]);
            }
        }
        return result;
    }
};
