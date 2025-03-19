#include <vector>

class SegmentTree
{
public:
    explicit SegmentTree(const std::vector<long long>& nums)
        : n(nums.size()), data(4 * n, 0), lazyAdd(4 * n, 0), lazyMulti(4 * n, 1)
    {
        build(0, n - 1, 1, nums);
    }

    // query the sum of nums[L:R], L and R are 0-indexed
    long long query(long long L, long long R) { return query(L, R, 0, n - 1, 1); }

    // add each element of nums[L:R] by delta, L and R are 0-indexed
    void add(long long L, long long R, long long delta) { add(L, R, delta, 0, n - 1, 1); }

    // multiply each element of nums[L:R] by factor, L and R are 0-indexed
    void multi(long long L, long long R, long long factor) { multi(L, R, factor, 0, n - 1, 1); }

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
