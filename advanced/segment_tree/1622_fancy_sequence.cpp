#include <vector>

/**
 * Write an API that generates fancy sequences using the append, addAll, and multAll operations.
 *
 * Implement the Fancy class:
 *
 * - Fancy() Initializes the object with an empty sequence.
 *
 * - void append(val) Appends an integer val to the end of the sequence.
 *
 * - void addAll(inc) Increments all existing values in the sequence by an integer inc.
 *
 * - void multAll(m) Multiplies all existing values in the sequence by an integer m.
 *
 * - int getIndex(idx) Gets the current value at index idx (0-indexed) of the sequence modulo 10^9
 * + 7. If the index is greater or equal than the length of the sequence, return -1.
 *
 * ! 1 <= val, inc, m <= 100
 * ! 0 <= idx <= 10^5
 * ! At most 10^5 calls total will be made to append, addAll, multAll, and getIndex.
 */

class SegmentTree {
public:
    explicit SegmentTree(const std::vector<long long>& nums)
        : n(nums.size()), data(4 * n, 0), lazyAdd(4 * n, 0), lazyMulti(4 * n, 1)
    {
        build(0, n - 1, 1, nums);
    }

    long long query(long long L, long long R)
    {
        return query(L, R, 0, n - 1, 1);
    }

    void add(long long L, long long R, long long delta)
    {
        add(L, R, delta, 0, n - 1, 1);
    }

    void multi(long long L, long long R, long long factor)
    {
        multi(L, R, factor, 0, n - 1, 1);
    }

private:
    void build(long long lo, long long hi, long long id, const std::vector<long long>& nums)
    {
        if (lo == hi) {
            data[id] = nums[lo];
            return;
        }
        const long long mid = lo + (hi - lo) / 2;
        build(lo, mid, 2 * id, nums);
        build(mid + 1, hi, 2 * id + 1, nums);
        data[id] = (data[2 * id] + data[2 * id + 1]) % kMod;
    }

    void propagate(long long lo, long long mid, long long hi, long long id)
    {
        const long long f = lazyMulti[id];
        const long long d = lazyAdd[id];
        data[2 * id] = (data[2 * id] * f % kMod + (mid - lo + 1) * d % kMod) % kMod;
        data[2 * id + 1] = (data[2 * id + 1] * f % kMod + (hi - mid) * d % kMod) % kMod;
        lazyMulti[2 * id] = lazyMulti[2 * id] * f % kMod;
        lazyMulti[2 * id + 1] = lazyMulti[2 * id + 1] * f % kMod;
        lazyMulti[id] = 1;
        lazyAdd[2 * id] = (lazyAdd[2 * id] * f % kMod + d) % kMod;
        lazyAdd[2 * id + 1] = (lazyAdd[2 * id + 1] * f % kMod + d) % kMod;
        lazyAdd[id] = 0;
    }

    long long query(long long L, long long R, long long lo, long long hi, long long id)
    {
        if (lo >= L && hi <= R)
            return data[id];

        const long long mid = lo + (hi - lo) / 2;
        propagate(lo, mid, hi, id);
        long long result = 0;
        if (mid >= L) {
            result = (result + query(L, R, lo, mid, 2 * id)) % kMod;
        }
        if (mid < R) {
            result = (result + query(L, R, mid + 1, hi, 2 * id + 1)) % kMod;
        }
        return result;
    }

    void add(long long L, long long R, long long delta, long long lo, long long hi, long long id)
    {
        if (lo >= L && hi <= R) {
            data[id] = (data[id] + (hi - lo + 1) * delta % kMod) % kMod;
            lazyAdd[id] = (lazyAdd[id] + delta) % kMod;
            return;
        }
        const long long mid = lo + (hi - lo) / 2;
        propagate(lo, mid, hi, id);
        if (mid >= L) {
            add(L, R, delta, lo, mid, 2 * id);
        }
        if (mid < R) {
            add(L, R, delta, mid + 1, hi, 2 * id + 1);
        }
        data[id] = (data[2 * id] + data[2 * id + 1]) % kMod;
    }

    void multi(long long L, long long R, long long factor, long long lo, long long hi, long long id)
    {
        if (lo >= L && hi <= R) {
            data[id] = data[id] * factor % kMod;
            lazyMulti[id] = lazyMulti[id] * factor % kMod;
            lazyAdd[id] = lazyAdd[id] * factor % kMod;
            return;
        }
        const long long mid = lo + (hi - lo) / 2;
        propagate(lo, mid, hi, id);
        if (mid >= L) {
            multi(L, R, factor, lo, mid, 2 * id);
        }
        if (mid < R) {
            multi(L, R, factor, mid + 1, hi, 2 * id + 1);
        }
        data[id] = (data[2 * id] + data[2 * id + 1]) % kMod;
    }

private:
    static constexpr long long kMod = 1e9 + 7;
    const long long n;
    std::vector<long long> data;
    std::vector<long long> lazyAdd;
    std::vector<long long> lazyMulti;
};

class Fancy {
public:
    Fancy() {}

    void append(int val)
    {
        tree.add(count, count, val);
        count++;
    }

    void addAll(int inc)
    {
        if (count == 0)
            return;

        tree.add(0, count - 1, inc);
    }

    void multAll(int m)
    {
        if (count == 0)
            return;

        tree.multi(0, count - 1, m);
    }

    int getIndex(int idx)
    {
        if (idx < 0 || idx >= count)
            return -1;

        return tree.query(idx, idx);
    }

private:
    SegmentTree tree{std::vector<long long>(1e5 + 1, 0LL)};
    int count{0};
};

/**
 * Your Fancy object will be instantiated and called as such:
 * Fancy* obj = new Fancy();
 * obj->append(val);
 * obj->addAll(inc);
 * obj->multAll(m);
 * int param_4 = obj->getIndex(idx);
 */
