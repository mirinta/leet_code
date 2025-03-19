#include <climits>
#include <vector>

class SegmentTree
{
public:
    explicit SegmentTree(const std::vector<long long>& nums)
        : n(nums.size()), data(4 * n, 0), lazy(4 * n, 0), flag(4 * n, false)
    {
        build(0, n - 1, 1, nums);
    }

    // query the max element of nums[L:R], L and R are 0-indexed
    long long query(long long L, long long R) { return query(L, R, 0, n - 1, 1); }

    // set all elements of nums[L:R] to val, L and R are 0-indexed
    void set(long long L, long long R, long long val) { set(L, R, val, 0, n - 1, 1); }

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
        data[id] = std::max(data[2 * id], data[2 * id + 1]);
    }

    long long query(long long L, long long R, long long lo, long long hi, long long id)
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
        const long long mid = lo + (hi - lo) / 2;
        long long result = LLONG_MIN;
        if (mid >= L) {
            result = std::max(result, query(L, R, lo, mid, 2 * id));
        }
        if (mid < R) {
            result = std::max(result, query(L, R, mid + 1, hi, 2 * id + 1));
        }
        return result;
    }

    void set(long long L, long long R, long long val, long long lo, long long hi, long long id)
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
        const long long mid = lo + (hi - lo) / 2;
        if (mid >= L) {
            set(L, R, val, lo, mid, 2 * id);
        }
        if (mid < R) {
            set(L, R, val, mid + 1, hi, 2 * id + 1);
        }
        data[id] = std::max(data[2 * id], data[2 * id + 1]);
    }

private:
    const long long n;
    std::vector<long long> data; // 1-indexed
    std::vector<long long> lazy; // 1-indexed
    std::vector<bool> flag;      // 1-indexed
};
