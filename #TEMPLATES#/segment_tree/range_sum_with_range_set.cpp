#include <vector>

class SegmentTree
{
public:
    explicit SegmentTree(const std::vector<long long>& nums)
        : n(nums.size()), data(4 * n, 0), lazy(4 * n, 0), flag(4 * n, false)
    {
        build(0, n - 1, 1, nums);
    }

    // query sum of nums[L:R], L and R are 0-indexed
    long long query(int L, int R) { return query(L, R, 0, n - 1, 1); }

    // set all elements of nums[L:R] to val, L and R are 0-indexed
    void set(int L, int R, long long val) { set(L, R, val, 0, n - 1, 1); }

private:
    void build(int lo, int hi, int id, const std::vector<long long>& nums)
    {
        if (lo == hi) {
            data[id] = nums[lo];
            return;
        }
        const int mid = lo + (hi - lo) / 2;
        build(lo, mid, 2 * id, nums);
        build(mid + 1, hi, 2 * id + 1, nums);
        data[id] = data[2 * id] + data[2 * id + 1];
    }

    long long query(int L, int R, int lo, int hi, int id)
    {
        if (lo >= L && hi <= R)
            return data[id];

        const int mid = lo + (hi - lo) / 2;
        if (flag[id]) {
            data[2 * id] = lazy[id] * (mid - lo + 1);
            data[2 * id + 1] = lazy[id] * (hi - mid);
            lazy[2 * id] = lazy[id];
            lazy[2 * id + 1] = lazy[id];
            flag[id] = false;
            flag[2 * id] = true;
            flag[2 * id + 1] = true;
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

    void set(int L, int R, long long val, int lo, int hi, int id)
    {
        if (lo >= L && hi <= R) {
            data[id] = val * (hi - lo + 1);
            lazy[id] = val;
            flag[id] = true;
            return;
        }
        const int mid = lo + (hi - lo) / 2;
        if (flag[id]) {
            data[2 * id] = lazy[id] * (mid - lo + 1);
            data[2 * id + 1] = lazy[id] * (hi - mid);
            lazy[2 * id] = lazy[id];
            lazy[2 * id + 1] = lazy[id];
            flag[id] = false;
            flag[2 * id] = true;
            flag[2 * id + 1] = true;
        }
        if (mid >= L) {
            set(L, R, val, lo, mid, 2 * id);
        }
        if (R > mid) {
            set(L, R, val, mid + 1, hi, 2 * id + 1);
        }
        data[id] = data[2 * id] + data[2 * id + 1];
    }

private:
    const int n;
    std::vector<long long> data; // 1-indexed
    std::vector<long long> lazy; // 1-indexed
    std::vector<bool> flag;      // 1-indexed
};
