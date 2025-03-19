#include <vector>

class SegmentTree
{
public:
    explicit SegmentTree(const std::vector<long long>& nums)
        : n(nums.size()), data(4 * n, 0), lazy(4 * n, 0)
    {
        build(0, n - 1, 1, nums);
    }

    // query sum of nums[L:R], L and R are 0-indexed
    long long query(long long L, long long R) { return query(L, R, 0, n - 1, 1); }

    // add each element of nums[L:R] by delta, L and R are 0-indexed
    void add(long long L, long long R, long long delta) { add(L, R, delta, 0, n - 1, 1); }

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
        data[id] = data[2 * id] + data[2 * id + 1];
    }

    long long query(long long L, long long R, long long lo, long long hi, long long id)
    {
        if (lo >= L && hi <= R)
            return data[id];

        const long long mid = lo + (hi - lo) / 2;
        if (lazy[id] != 0) {
            data[2 * id] += lazy[id] * (mid - lo + 1);
            data[2 * id + 1] += lazy[id] * (hi - mid);
            lazy[2 * id] += lazy[id];
            lazy[2 * id + 1] += lazy[id];
            lazy[id] = 0;
        }
        long long result = 0;
        if (mid >= L) {
            result += query(L, R, lo, mid, 2 * id);
        }
        if (R > mid) {
            result += query(L, R, mid + 1, hi, 2 * id + 1);
        }
        return result;
    }

    void add(long long L, long long R, long long delta, long long lo, long long hi, long long id)
    {
        if (lo >= L && hi <= R) {
            data[id] += delta * (hi - lo + 1);
            lazy[id] += delta;
            return;
        }
        const long long mid = lo + (hi - lo) / 2;
        if (lazy[id] != 0) {
            data[2 * id] += lazy[id] * (mid - lo + 1);
            data[2 * id + 1] += lazy[id] * (hi - mid);
            lazy[2 * id] += lazy[id];
            lazy[2 * id + 1] += lazy[id];
            lazy[id] = 0;
        }
        if (mid >= L) {
            add(L, R, delta, lo, mid, 2 * id);
        }
        if (R > mid) {
            add(L, R, delta, mid + 1, hi, 2 * id + 1);
        }
        data[id] = data[2 * id] + data[2 * id + 1];
    }

private:
    const long long n;
    std::vector<long long> data; // 1-indexed
    std::vector<long long> lazy; // 1-indexed
};
