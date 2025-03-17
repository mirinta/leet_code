#include <numeric>
#include <vector>

/**
 * You are given two 0-indexed arrays nums1 and nums2 and a 2D array queries of queries. There are
 * three types of queries:
 *
 * 1. For a query of type 1, queries[i] = [1, l, r]. Flip the values from 0 to 1 and from 1 to 0 in
 * nums1 from index l to index r. Both l and r are 0-indexed.
 *
 * 2. For a query of type 2, queries[i] = [2, p, 0]. For every index 0 <= i < n, set nums2[i] =
 * nums2[i] + nums1[i] * p.
 *
 * 3. For a query of type 3, queries[i] = [3, 0, 0]. Find the sum of the elements in nums2.
 *
 * Return an array containing all the answers to the third type queries.
 *
 * ! 1 <= nums1.length,nums2.length <= 10^5
 * ! nums1.length = nums2.length
 * ! 1 <= queries.length <= 10^5
 * ! queries[i].length = 3
 * ! 0 <= l <= r <= nums1.length - 1
 * ! 0 <= p <= 10^6
 * ! 0 <= nums1[i] <= 1
 * ! 0 <= nums2[i] <= 10^9
 */

class SegmentTree
{
public:
    explicit SegmentTree(const std::vector<int>& nums)
        : n(nums.size()), data(4 * n + 1, 0), lazy(4 * n + 1, 0)
    {
        build(0, n - 1, 1, nums);
    }

    long long query(int L, int R) { return query(L, R, 0, n - 1, 1); }

    void flip(int L, int R) { flip(L, R, 0, n - 1, 1); }

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
        data[id] = data[2 * id] + data[2 * id + 1];
    }

    long long query(int L, int R, int lo, int hi, int id)
    {
        if (lo >= L && hi <= R)
            return data[id];

        const int mid = lo + (hi - lo) / 2;
        if (lazy[id]) {
            data[2 * id] = (mid - lo + 1) - data[2 * id];
            data[2 * id + 1] = (hi - mid) - data[2 * id + 1];
            lazy[2 * id] = !lazy[2 * id];
            lazy[2 * id + 1] = !lazy[2 * id + 1];
            lazy[id] = false;
        }
        long long result = 0;
        if (mid >= L) {
            result += query(L, R, lo, mid, 2 * id);
        }
        if (mid < R) {
            result += query(L, R, mid + 1, hi, 2 * id + 1);
        }
        return result;
    }

    void flip(int L, int R, int lo, int hi, int id)
    {
        if (lo >= L && hi <= R) {
            data[id] = (hi - lo + 1) - data[id];
            lazy[id] = !lazy[id];
            return;
        }
        const int mid = lo + (hi - lo) / 2;
        if (lazy[id]) {
            data[2 * id] = (mid - lo + 1) - data[2 * id];
            data[2 * id + 1] = (hi - mid) - data[2 * id + 1];
            lazy[2 * id] = !lazy[2 * id];
            lazy[2 * id + 1] = !lazy[2 * id + 1];
            lazy[id] = false;
        }
        if (mid >= L) {
            flip(L, R, lo, mid, 2 * id);
        }
        if (mid < R) {
            flip(L, R, mid + 1, hi, 2 * id + 1);
        }
        data[id] = data[2 * id] + data[2 * id + 1];
    }

private:
    const int n;
    std::vector<long long> data;
    std::vector<bool> lazy;
};

class Solution
{
public:
    std::vector<long long> handleQuery(std::vector<int>& nums1, std::vector<int>& nums2,
                                       std::vector<std::vector<int>>& queries)
    {
        SegmentTree tree(nums1);
        long long sum = std::accumulate(nums2.begin(), nums2.end(), 0LL);
        std::vector<long long> result;
        for (const auto& q : queries) {
            if (q[0] == 1) {
                tree.flip(q[1], q[2]);
            } else if (q[0] == 2) {
                sum += tree.query(0, nums1.size() - 1) * q[1];
            } else {
                result.push_back(sum);
            }
        }
        return result;
    }
};
