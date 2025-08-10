#include <climits>
#include <vector>

/**
 * You are given two arrays of integers, fruits and baskets, each of length n, where fruits[i]
 * represents the quantity of the ith type of fruit, and baskets[j] represents the capacity of the
 * jth basket.
 *
 * From left to right, place the fruits according to these rules:
 *
 * - Each fruit type must be placed in the leftmost available basket with a capacity greater than or
 * equal to the quantity of that fruit type.
 *
 * - Each basket can hold only one type of fruit.
 *
 * - If a fruit type cannot be placed in any basket, it remains unplaced.
 *
 * Return the number of fruit types that remain unplaced after all possible allocations are made.
 *
 * ! n == fruits.length == baskets.length
 * ! 1 <= n <= 10^5
 * ! 1 <= fruits[i], baskets[i] <= 10^9
 */

class SegmentTree
{
public:
    explicit SegmentTree(const std::vector<int>& nums)
        : n(nums.size()), data(4 * n, 0), lazy(4 * n, 0), flag(4 * n, false)
    {
        build(0, n - 1, 1, nums);
    }

    // query the max element of nums[L:R], L and R are 0-indexed
    int query(int L, int R) { return query(L, R, 0, n - 1, 1); }

    // set all elements of nums[L:R] to val, L and R are 0-indexed
    void set(int L, int R, int val) { set(L, R, val, 0, n - 1, 1); }

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

class Solution
{
public:
    int numOfUnplacedFruits(std::vector<int>& fruits, std::vector<int>& baskets)
    {
        const int n = baskets.size();
        SegmentTree tree(baskets);
        int result = 0;
        for (const auto& val : fruits) {
            int lo = 0;
            int hi = n - 1;
            while (lo <= hi) {
                const int mid = lo + (hi - lo) / 2;
                if (tree.query(0, mid) >= val) {
                    hi = mid - 1;
                } else {
                    lo = mid + 1;
                }
            }
            if (lo < n && baskets[lo] >= val) {
                tree.set(lo, lo, INT_MIN);
            } else {
                result++;
            }
        }
        return result;
    }
};
